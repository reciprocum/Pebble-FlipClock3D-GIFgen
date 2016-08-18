/*
   Project: GIFgen
   File   : main.c
   Author : Afonso Santos, Portugal

   Last revision: 14h35 August 14 2016
*/

#include "Config.h"
#include <pebble.h>
#include "FastMath.h"
#include "R3.h"
#include "Cam3D.h"
#include "TransformR3.h"
#include "Clock3D.h"
#include "Interpolations.h"
#include "main.h"


// GIF related
static int        gifStep   = 0 ;

// UI related
static Window         *window ;
static Layer          *world_layer ;
static ActionBarLayer *action_bar;

// World related
typedef enum { WORLD_MODE_UNDEFINED
             , WORLD_MODE_LAUNCH
             , WORLD_MODE_PARK
             , WORLD_MODE_STEADY
             }
WorldMode ;


static WorldMode    world_mode    = WORLD_MODE_UNDEFINED ;

float    *spinRotationFraction    = NULL ;   // To be allocated at world_initialize( ).
float    *animRotationFraction    = NULL ;   // To be allocated at world_initialize( ).
float    *animTranslationFraction = NULL ;   // To be allocated at world_initialize( ).

// This variable is critical to the draw_mesh algorithm.
// Used to pre-calculate (only once per vertex) the screen coordinates of the vertexes (after 3D->2D camera projected).

// Spin(Z) CONSTANTS & variables
#define        SPIN_ROTATION_HHMM     -DEG_045

static float   spin_rotation  = SPIN_ROTATION_HHMM ;   // Initial spin rotation angle allows to view hours/minutes faces.


// Camera related
#define  CAM_DISTANCE           (2.2 * CUBE_SIZE)
#define  CAM_VIEWPOINT_STEADY   (R3){ .x = -0.1f, .y = 1.0f, .z = 0.7f }

static Cam3D  cam ;
static float  cam_zoom = PBL_IF_RECT_ELSE(1.25f, 1.14f) ;


// Forward declarations.
void  set_world_mode( WorldMode pWorldMode ) ;
void  world_update_timer_handler( void *data ) ;


// Animation related
static int    park_animStep    = -1 ;
static float  park_animRange ;
static int    launch_animStep  = -1 ;
//static float  launch_animRange = DEG_090 ;
static float  launch_animRange = DEG_135 ;


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

  Clock3D_setTime_DDHHMMSS( clockDD, clockHH, clockMM, clockSS ) ;
}


void
gifStepper_advance_click_handler
( ClickRecognizerRef recognizer
, void              *context
)
{
  ++gifStep ;
  app_timer_register( ANIMATION_INTERVAL_MS, world_update_timer_handler, NULL ) ;   // Schedule a world update.
}


void
gifStepper_jump_click_handler
( ClickRecognizerRef recognizer
, void              *context
)
{
  gifStep += 176 - ANIMATION_FLIP_STEPS ;  // Advance 1 minute
  app_timer_register( ANIMATION_INTERVAL_MS, world_update_timer_handler, NULL ) ;   // Schedule a world update.
}


void
gifStepper_reset_click_handler
( ClickRecognizerRef recognizer
, void              *context
)
{
  gifStep = 0 ;
  set_world_mode( WORLD_MODE_LAUNCH ) ;
  app_timer_register( ANIMATION_INTERVAL_MS, world_update_timer_handler, NULL ) ;   // Schedule a world update.
}


void
animateAll_click_handler
( ClickRecognizerRef recognizer
, void              *context
)
{
  Clock3D_animateAll( ) ;
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
( R3         *viewPoint
, const float rotationZ
)
{
  // setup 3D camera
  Cam3D_lookAtOriginUpwards( &cam
                           , TransformR3_rotateZ( R3_scale( CAM_DISTANCE    // View point.
                                                          , viewPoint
                                                          )
                                                , rotationZ
                                                )
                           , cam_zoom                                       // Zoom
                           , CAM3D_PROJECTION_PERSPECTIVE
                           ) ;
}


void
set_world_mode
( WorldMode pWorldMode )
{
#ifdef LOG
  APP_LOG( APP_LOG_LEVEL_DEBUG, "set_world_mode:: pWorldMode = %d", pWorldMode ) ;
#endif

  // Start-up entering mode. Subscribe to newly needed services. Apply relevant configurations.
  switch (world_mode = pWorldMode)
  {
    case WORLD_MODE_LAUNCH:
      launch_animStep = ANIMATION_SPIN_STEPS ;
      break ;

    case WORLD_MODE_PARK:
      park_animStep  = ANIMATION_SPIN_STEPS ;
      park_animRange = spin_rotation - SPIN_ROTATION_HHMM ;    // From current rotation.
      break ;

    default:
      break ;
  }
}


void
world_initialize
( )
{
  Clock3D_initialize( ) ;

  fillInterpolator_AccelerateDecelerate( spinRotationFraction = malloc((ANIMATION_SPIN_STEPS+1)*sizeof(float))
                                       , ANIMATION_SPIN_STEPS
                                       ) ;

  fillInterpolator_AccelerateDecelerate( animRotationFraction = malloc((ANIMATION_FLIP_STEPS+1)*sizeof(float))
                                       , ANIMATION_FLIP_STEPS
                                       ) ;

  fillInterpolator_TrigonometricYoYo( animTranslationFraction = malloc((ANIMATION_FLIP_STEPS+1)*sizeof(float))
                                    , ANIMATION_FLIP_STEPS
                                    ) ;

  Clock3D_config( SEG_NCURVYSKIN ) ;

  // Set initial world mode.
  set_world_mode( WORLD_MODE_LAUNCH ) ;
}


void
world_finalize
( )
{
  Clock3D_finalize( ) ;

  free( animRotationFraction    ) ; animRotationFraction    = NULL ;
  free( animTranslationFraction ) ; animTranslationFraction = NULL ;
  free( spinRotationFraction    ) ; spinRotationFraction    = NULL ;
}


// UPDATE CAMERA & WORLD OBJECTS PROPERTIES

void
world_update
( )
{
  clock_updateTime( gifStep ) ;
  Clock3D_updateAnimation( ANIMATION_FLIP_STEPS ) ;

  float cam_rotation ;

  switch (world_mode)
  {
    case WORLD_MODE_LAUNCH:
      if (launch_animStep >= 0)
        cam_rotation = SPIN_ROTATION_HHMM  +  (1.0 - spinRotationFraction[launch_animStep--]) * launch_animRange ;
      else
      {
        cam_rotation = spin_rotation = SPIN_ROTATION_HHMM + launch_animRange ;
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
  layer_mark_dirty( world_layer ) ;
}


void
world_update_timer_handler
( void *data )
{
  world_update( ) ;

  // Call me again ?
  if (gifStep < GIF_FRAME_STOP)
  {
    ++gifStep ;
    app_timer_register( ANIMATION_INTERVAL_MS, world_update_timer_handler, data ) ;  // Schedule next animation frame.
  }
}


void
world_draw
( Layer    *me
, GContext *gCtx
)
{
#ifdef LOG
  APP_LOG( APP_LOG_LEVEL_DEBUG, "world_draw:: gifStep = %d", gifStep ) ;
#endif

  const GRect layerBounds = layer_get_bounds( me ) ;
  const uint8_t w = layerBounds.size.w ;
  const uint8_t h = layerBounds.size.h ;

  Clock3D_draw( gCtx, &cam, w, h, TRANSPARENCY_DEFAULT ) ;
}


void
window_load
( Window *window )
{
  Layer *window_root_layer = window_get_root_layer( window ) ;

  action_bar = action_bar_layer_create( ) ;
  action_bar_layer_add_to_window( action_bar, window ) ;
  action_bar_layer_set_click_config_provider( action_bar, gifStepper_click_config_provider ) ;

  GRect bounds = layer_get_frame( window_root_layer ) ;
  world_layer = layer_create( bounds ) ;
  layer_set_update_proc( world_layer, world_draw ) ;
  layer_add_child( window_root_layer, world_layer ) ;

  app_timer_register( ANIMATION_INTERVAL_MS, world_update_timer_handler, NULL ) ;  // Schedule first world update.
}


void
window_unload
( Window *window )
{
  layer_destroy( world_layer ) ;
}


void
app_initialize
( void )
{
  world_initialize( ) ;

  window = window_create( ) ;
  window_set_background_color( window, GColorBlack ) ;
 
  window_set_window_handlers( window
                            , (WindowHandlers)
                              { .load   = window_load
                              , .unload = window_unload
                              }
                            ) ;

  window_stack_push( window, false ) ;
}


void
app_finalize
( void )
{
  window_stack_remove( window, false ) ;
  window_destroy( window ) ;
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