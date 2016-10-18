/*
   Project: FlipClock3D (GIFgen)
   File   : main.c
   Author : Afonso Santos, Portugal

   Last revision: 15h44 September 03 2016  GMT
*/

#include <pebble.h>
#include <karambola/FastMath.h>
#include <karambola/R3.h>
#include <karambola/Interpolator.h>
#include <karambola/CamR3.h>
#include <karambola/TransformR3.h>
#include <karambola/Clock3D.h>

#include "Config.h"
#include "main.h"

// Obstruction related.
GSize available_screen ;


// GIF related
static int        s_gifStep   = 0 ;

// UI related
static Window         *s_window ;
static Layer          *s_window_layer ;
static Layer          *s_world_layer ;
static ActionBarLayer *s_action_bar;


static WorldMode    s_world_mode  = WORLD_MODE_UNDEFINED ;

float    *spinRotationFraction    = NULL ;   // To be allocated at world_initialize( ).
float    *animRotationFraction    = NULL ;   // To be allocated at world_initialize( ).
float    *animTranslationFraction = NULL ;   // To be allocated at world_initialize( ).

// This variable is critical to the draw_mesh algorithm.
// Used to pre-calculate (only once per vertex) the screen coordinates of the vertexes (after 3D->2D camera projected).

// Spin(Z) CONSTANTS & variables
#define        SPIN_ROTATION_HHMM     -DEG_045

static float   s_spin_rotation  = SPIN_ROTATION_HHMM ;   // Initial spin rotation angle allows to view hours/minutes faces.


// Camera related
#define  CAM_DISTANCE           (+2.2f * CUBE_SIZE)
#define  CAM_VIEWPOINT_STEADY   (R3){ .x = -0.1f, .y = +1.0f, .z = +0.7f }

static CamR3  s_cam ;
static float  s_cam_zoom = PBL_IF_RECT_ELSE(+1.25f, +1.14f) ;


// Animation related
static int    park_animStep    = -1 ;
static float  park_animRange ;
static int    launch_animStep  = -1 ;
static float  launch_animRange = DEG_135 ;


static Clock3D           s_clock ;  // The main/only world object.
static MeshTransparency  s_clock_transparency = CLOCK_TRANSPARENCY_DEFAULT ;

void
clock_updateTime
( const int pTick )
{
  const int elapsedSec = pTick / GIF_SLOWDOWN_FACTOR  ;
  const int timeSec    = 60 * (60 * (24 * GIF_BASE_DD  +  GIF_BASE_HH)  +  GIF_BASE_MM)   +  GIF_BASE_SS  + elapsedSec ;

  const int clockDD = (timeSec / (24*60*60))      ;
  const int clockHH = (timeSec / (60*60))    % 24 ;
  const int clockMM = (timeSec / 60)         % 60 ;
  const int clockSS = timeSec                % 60 ;

  Clock3D_setTime_DDHHMMSS( &s_clock, clockDD, clockHH, clockMM, clockSS ) ;
}


void
gifStepper_advance_click_handler
( ClickRecognizerRef recognizer
, void              *context
)
{
  ++s_gifStep ;
  app_timer_register( 0, world_update_timer_handler, NULL ) ;   // Schedule a world update.
}


void
gifStepper_jump_click_handler
( ClickRecognizerRef recognizer
, void              *context
)
{
  s_gifStep += 176 - ANIMATION_FLIP_STEPS ;  // Advance 1 minute
  app_timer_register( 0, world_update_timer_handler, NULL ) ;   // Schedule a world update.
}


void
gifStepper_reset_click_handler
( ClickRecognizerRef recognizer
, void              *context
)
{
  s_gifStep = 0 ;
  set_world_mode( WORLD_MODE_LAUNCH ) ;
  app_timer_register( 0, world_update_timer_handler, NULL ) ;   // Schedule a world update.
}


void
animateAll_click_handler
( ClickRecognizerRef recognizer
, void              *context
)
{
  Clock3D_animateAll( &s_clock ) ;
  app_timer_register( ANIMATION_INTERVAL_MS, world_update_timer_handler, NULL ) ;   // Schedule a world update.
}


void
gifStepper_click_config_provider
( void *context )
{
  window_single_click_subscribe( BUTTON_ID_UP
                               , (ClickHandler) gifStepper_jump_click_handler
                               ) ;

  window_single_click_subscribe( BUTTON_ID_SELECT
                               , (ClickHandler) gifStepper_advance_click_handler
                               ) ;

  window_single_click_subscribe( BUTTON_ID_DOWN
                               , (ClickHandler) animateAll_click_handler
                               ) ;
}


void
cam_config
( const R3   *pViewPoint
, const float pRotZrad
)
{
  R3 scaledVP ;
  R3_scaTo( &scaledVP, CAM_DISTANCE, pViewPoint ) ;

  R3 rotatedVP ;
  R3_rotZrad( &rotatedVP, &scaledVP, pRotZrad ) ;

  // setup 3D camera
  CamR3_lookAtOriginUpwards( &s_cam, &rotatedVP, s_cam_zoom, CAM_PROJECTION_PERSPECTIVE ) ;
}


static
void
set_world_mode
( WorldMode pWorldMode )
{
  LOGD( "set_world_mode:: pWorldMode = %d", pWorldMode ) ;

  // Start-up entering mode. Subscribe to newly needed services. Apply relevant configurations.
  switch (s_world_mode = pWorldMode)
  {
    case WORLD_MODE_LAUNCH:
      launch_animStep = ANIMATION_SPIN_STEPS ;
      break ;

    case WORLD_MODE_PARK:
      park_animStep  = ANIMATION_SPIN_STEPS ;
      park_animRange = s_spin_rotation - SPIN_ROTATION_HHMM ;    // From current rotation.
      break ;

    default:
      break ;
  }
}


static
void
interpolations_initialize
( )
{
  Interpolator_AccelerateDecelerate( spinRotationFraction = malloc((ANIMATION_SPIN_STEPS+1)*sizeof(float))
                                   , ANIMATION_SPIN_STEPS
                                   ) ;

  Interpolator_AccelerateDecelerate( animRotationFraction = malloc((ANIMATION_FLIP_STEPS+1)*sizeof(float))
                                   , ANIMATION_FLIP_STEPS
                                   ) ;

  Interpolator_SinYoYo( animTranslationFraction = malloc((ANIMATION_FLIP_STEPS+1)*sizeof(float))
                      , ANIMATION_FLIP_STEPS
                      ) ;
}


static
void
world_initialize
( )
{
  Clock3D_initialize( &s_clock ) ;
  interpolations_initialize( ) ;
  Clock3D_config( &s_clock, DIGIT2D_CURVYSKIN ) ;

  // Set initial world mode.
  set_world_mode( WORLD_MODE_LAUNCH ) ;
}


static
void
interpolations_finalize
( )
{
  free( animRotationFraction    ) ; animRotationFraction    = NULL ;
  free( animTranslationFraction ) ; animTranslationFraction = NULL ;
  free( spinRotationFraction    ) ; spinRotationFraction    = NULL ;
}


static
void
world_finalize
( )
{
  Clock3D_finalize( &s_clock ) ;
  interpolations_finalize( ) ;
}


// UPDATE CAMERA & WORLD OBJECTS PROPERTIES

static
void
world_update
( )
{
  clock_updateTime( s_gifStep ) ;
  Clock3D_updateAnimation( &s_clock, ANIMATION_FLIP_STEPS ) ;

  float cam_rotation ;

  switch (s_world_mode)
  {
    case WORLD_MODE_LAUNCH:
      if (launch_animStep >= 0)
        cam_rotation = SPIN_ROTATION_HHMM  +  (1.0 - spinRotationFraction[launch_animStep--]) * launch_animRange ;
      else
      {
        cam_rotation = s_spin_rotation = SPIN_ROTATION_HHMM + launch_animRange ;
        set_world_mode( WORLD_MODE_PARK ) ;
      }
  
      break ;
  
    case WORLD_MODE_PARK:
      if (park_animStep >= 0)
        cam_rotation = SPIN_ROTATION_HHMM  +  spinRotationFraction[park_animStep--] * park_animRange ;
      else
      {
        cam_rotation = SPIN_ROTATION_HHMM ;
        set_world_mode( WORLD_MODE_STEADY ) ;
      }
  
      break ;
  
    default:
      cam_rotation = SPIN_ROTATION_HHMM ;
    break ;
  }

  cam_config( &CAM_VIEWPOINT_STEADY, cam_rotation ) ;

  // this will queue a defered call to the world_draw( ) method.
  layer_mark_dirty( s_world_layer ) ;
}


static
void
world_update_timer_handler
( void *data )
{
  world_update( ) ;

  // Call me again ?
  if (s_gifStep < GIF_STOP_COUNT)
  {
    ++s_gifStep ;
    app_timer_register( ANIMATION_INTERVAL_MS, world_update_timer_handler, data ) ;  // Schedule next animation frame.
  }
}


void
world_draw
( Layer    *me
, GContext *gCtx
)
{
  LOGD( "world_draw:: s_gifStep = %d", s_gifStep ) ;

  Clock3D_draw( gCtx, &s_clock, &s_cam, available_screen.w, available_screen.h, s_clock_transparency ) ;
}


void
unobstructed_area_change_handler
( AnimationProgress progress
, void             *context
)
{
  available_screen = layer_get_unobstructed_bounds( s_window_layer ).size ;
}


void
window_load
( Window *s_window )
{
  s_window_layer    = window_get_root_layer( s_window ) ;
  available_screen  = layer_get_unobstructed_bounds( s_window_layer ).size ;

  s_action_bar = action_bar_layer_create( ) ;
  action_bar_layer_add_to_window( s_action_bar, s_window ) ;
  action_bar_layer_set_click_config_provider( s_action_bar, gifStepper_click_config_provider ) ;

  GRect bounds = layer_get_frame( s_window_layer ) ;
  s_world_layer = layer_create( bounds ) ;
  layer_set_update_proc( s_world_layer, world_draw ) ;
  layer_add_child( s_window_layer, s_world_layer ) ;

  // Obstrution handling.
  UnobstructedAreaHandlers unobstructed_area_handlers = { .change = unobstructed_area_change_handler } ;
  unobstructed_area_service_subscribe( unobstructed_area_handlers, NULL ) ;
  
  app_timer_register( 0, world_update_timer_handler, NULL ) ;  // Schedule first world update.
}


void
window_unload
( Window *s_window )
{
  unobstructed_area_service_unsubscribe( ) ;

  layer_destroy( s_world_layer ) ;
}


void
app_initialize
( void )
{
  world_initialize( ) ;

  s_window = window_create( ) ;
  window_set_background_color( s_window, GColorBlack ) ;
 
  window_set_window_handlers( s_window
                            , (WindowHandlers)
                              { .load   = window_load
                              , .unload = window_unload
                              }
                            ) ;

  window_stack_push( s_window, false ) ;
}


void
app_finalize
( void )
{
  window_stack_remove( s_window, false ) ;
  window_destroy( s_window ) ;
  world_finalize( ) ;
}


int
main
( void )
{
  app_initialize( ) ;
  app_event_loop( ) ;
  app_finalize( ) ;
}