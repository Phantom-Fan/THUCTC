cc_library(
	name = 'classify',
	srcs = [
		'BasicTextClassifier.cpp',
        'LiblinearTextClassifier.cpp',
        'Lexicon.cpp',
        'DocumentVector.cpp',
        'BigramWordSegment.cpp',
        'LangUtils.cpp',
        './liblinear-2.1/linear.cpp',
        './liblinear-2.1/tron.cpp',
        './liblinear-2.1/blas/daxpy.c',
        './liblinear-2.1/blas/ddot.c',
        './liblinear-2.1/blas/dnrm2.c',
        './liblinear-2.1/blas/dscal.c',
	],
	export_incs = ['.','./liblinear-2.1','./liblinear-2.1/blas','./utf8'],
	extra_cppflags = [
        '-Wall',
        '-std=c++11',
    ],
)