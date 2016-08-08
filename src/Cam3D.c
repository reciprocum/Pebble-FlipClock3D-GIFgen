/*
   File  : Cam3D.c
   Author: Afonso Santos, Portugal

   Last revision: 12h55 August 05 2016
*/

#include "Config.h"
#include "R2.h"
#include "Cam3D.h"


Cam3D*
Cam3D_setup
( Cam3D        *cam
, const R3     *viewPoint
, const R3     *lookingAt
, const R3     *upReference
, const float   zoom
, const uint8_t projectionMode
)
{
  R3_assign( &cam->viewPoint, viewPoint ) ;

  R3_versor( R3_subtract( &cam->zAxis, lookingAt, &cam->viewPoint ) ) ;	    // zAxis = versor( lookingAt - viewPoint )
  R3_versor( R3_crossProduct( &cam->xAxis, &cam->zAxis, upReference ) ) ;	  // xAxis = versor( zAxis X upReference  )
  R3_crossProduct( &cam->yAxis, &cam->zAxis, &cam->xAxis ) ;                // yAxis = zAxis X xAxis
  cam->zoom           = zoom ;
  cam->projectionMode = projectionMode ;

  return cam ;
}


R2*
Cam3D_view
( R2           *v2D      // camera's film plane 2D coordinates of 3D world point
, const Cam3D  *cam      // camera used to view the 3D point
, const R3     *v3D      // world point's 3D coordinates
)
{
  static R3 vCam ;

  R3_subtract( &vCam, v3D, &cam->viewPoint ) ;			      // vCamera = norm( v - Eye )

  float x = R3_dotProduct( &cam->xAxis, &vCam ) ;
  float y = R3_dotProduct( &cam->yAxis, &vCam ) ;
  float z = R3_dotProduct( &cam->zAxis, &vCam ) ;

  // TODO: z cliping & projectionMode awareness.
  float k = cam->zoom / z ;

  return R2_set( v2D, k*x, k*y ) ;
}