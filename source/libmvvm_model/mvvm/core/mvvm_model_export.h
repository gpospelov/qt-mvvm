
#ifndef MVVM_MODEL_EXPORT_H
#define MVVM_MODEL_EXPORT_H

#ifdef MVVM_MODEL_STATIC_DEFINE
#  define MVVM_MODEL_EXPORT
#  define MVVM_MODEL_NO_EXPORT
#else
#  ifndef MVVM_MODEL_EXPORT
#    ifdef mvvm_model_EXPORTS
        /* We are building this library */
#      define MVVM_MODEL_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define MVVM_MODEL_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef MVVM_MODEL_NO_EXPORT
#    define MVVM_MODEL_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef MVVM_MODEL_DEPRECATED
#  define MVVM_MODEL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MVVM_MODEL_DEPRECATED_EXPORT
#  define MVVM_MODEL_DEPRECATED_EXPORT MVVM_MODEL_EXPORT MVVM_MODEL_DEPRECATED
#endif

#ifndef MVVM_MODEL_DEPRECATED_NO_EXPORT
#  define MVVM_MODEL_DEPRECATED_NO_EXPORT MVVM_MODEL_NO_EXPORT MVVM_MODEL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MVVM_MODEL_NO_DEPRECATED
#    define MVVM_MODEL_NO_DEPRECATED
#  endif
#endif

#endif /* MVVM_MODEL_EXPORT_H */
