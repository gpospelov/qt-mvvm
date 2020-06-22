
#ifndef MVVM_VIEWMODEL_EXPORT_H
#define MVVM_VIEWMODEL_EXPORT_H

#ifdef MVVM_VIEWMODEL_STATIC_DEFINE
#  define MVVM_VIEWMODEL_EXPORT
#  define MVVM_VIEWMODEL_NO_EXPORT
#else
#  ifndef MVVM_VIEWMODEL_EXPORT
#    ifdef mvvm_viewmodel_EXPORTS
        /* We are building this library */
#      define MVVM_VIEWMODEL_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define MVVM_VIEWMODEL_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef MVVM_VIEWMODEL_NO_EXPORT
#    define MVVM_VIEWMODEL_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef MVVM_VIEWMODEL_DEPRECATED
#  define MVVM_VIEWMODEL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MVVM_VIEWMODEL_DEPRECATED_EXPORT
#  define MVVM_VIEWMODEL_DEPRECATED_EXPORT MVVM_VIEWMODEL_EXPORT MVVM_VIEWMODEL_DEPRECATED
#endif

#ifndef MVVM_VIEWMODEL_DEPRECATED_NO_EXPORT
#  define MVVM_VIEWMODEL_DEPRECATED_NO_EXPORT MVVM_VIEWMODEL_NO_EXPORT MVVM_VIEWMODEL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MVVM_VIEWMODEL_NO_DEPRECATED
#    define MVVM_VIEWMODEL_NO_DEPRECATED
#  endif
#endif

#endif /* MVVM_VIEWMODEL_EXPORT_H */
