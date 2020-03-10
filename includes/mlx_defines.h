#ifndef MLX_DEFINES_H
# define MLX_DEFINES_H

# ifdef __unix__

#  define WIDTH				1000
#  define HEIGHT			1000

#  define ESC			65307

#  define MINUS			45
#  define PLUS			61

#  define SPACE			32

#  define W				119
#  define S				115
#  define A				97
#  define D				100

#  define Q				113
#  define E				101

#  define UP			65362
#  define DOWN			65364
#  define LEFT			65361
#  define RIGHT			65363

#  define I				105

#  define WHEEL_UP		5
#  define WHEEL_DOWN	4

#  define LEFT_BUTTON	1
#  define RIGHT_BUTTON	3

#  define TAB			65289

#  define LESS			(44)
#  define MORE			(46)


# else

// #  define WIDTH		2500
// #  define HEIGHT		1350
#  define WIDTH			1000
#  define HEIGHT		1000

#  define ESC			53

#  define MINUS			27
#  define PLUS			24

#  define SPACE			49

#  define W				13
#  define S				1
#  define A				0
#  define D				2

#  define Q				12
#  define E				14

#  define UP			126
#  define DOWN			125
#  define LEFT			123
#  define RIGHT			124

#  define I				34
#  define T				17

#  define WHEEL_UP		5
#  define WHEEL_DOWN	4

#  define LEFT_BUTTON	1
#  define RIGHT_BUTTON	2

#  define TAB			48

#  define NUM_PLUS		69
#  define NUM_MINUS		78

# endif

# define MAX_X				(WIDTH - 1)
# define MAX_Y				(HEIGHT - 1)
# define COMPLEX_CENTER_X	(WIDTH / 2)
# define COMPLEX_CENTER_Y	(HEIGHT / 2)

# define __WHITE		16777215
# define __BLACK		0

#endif