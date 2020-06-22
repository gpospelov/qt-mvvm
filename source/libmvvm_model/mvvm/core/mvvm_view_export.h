
#ifndef MVVM_VIEW_EXPORT_H
#define MVVM_VIEW_EXPORT_H

#ifdef MVVM_VIEW_STATIC_DEFINE
#  define MVVM_VIEW_EXPORT
#  define MVVM_VIEW_NO_EXPORT
#else
#  ifndef MVVM_VIEW_EXPORT
#    ifdef mvvm_view_EXPORTS
        /* We are building this library */
#      define MVVM_VIEW_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define MVVM_VIEW_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef MVVM_VIEW_NO_EXPORT
#    define MVVM_VIEW_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef MVVM_VIEW_DEPRECATED
#  define MVVM_VIEW_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MVVM_VIEW_DEPRECATED_EXPORT
#  define MVVM_VIEW_DEPRECATED_EXPORT MVVM_VIEW_EXPORT MVVM_VIEW_DEPRECATED
#endif

#ifndef MVVM_VIEW_DEPRECATED_NO_EXPORT
#  define MVVM_VIEW_DEPRECATED_NO_EXPORT MVVM_VIEW_NO_EXPORT MVVM_VIEW_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MVVM_VIEW_NO_DEPRECATED
#    define MVVM_VIEW_NO_DEPRECATED
#  endif
#endif

#endif /* MVVM_VIEW_EXPORT_H */
