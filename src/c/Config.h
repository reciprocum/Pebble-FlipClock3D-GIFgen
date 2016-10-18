/*
   Project: FlipClock3D (GIFgen)
   File   : Config.h
   Author : Afonso Santos, Portugal

   Last revision: 15h44 September 03 2016  GMT
*/

#pragma once

// Uncommenting the next line will enable all LOG* calls.
//#define LOG

#ifdef LOG
  #define LOGD(fmt, ...) APP_LOG(APP_LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
  #define LOGI(fmt, ...) APP_LOG(APP_LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
  #define LOGW(fmt, ...) APP_LOG(APP_LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
  #define LOGE(fmt, ...) APP_LOG(APP_LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#else
  #define LOGD(fmt, ...)
  #define LOGI(fmt, ...)
  #define LOGW(fmt, ...)
  #define LOGE(fmt, ...)
#endif