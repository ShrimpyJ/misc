#ifndef PF_MATH_H
#define PF_MATH_H

#include <GL/glew.h>
#include <stdio.h>
#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif
#ifndef __USE_MISC
	#define __USE_MISC
#endif
#include <math.h>

#define DEG_TO_RAD(_deg) ((_deg)*(M_PI/180.0f))
#define RAD_TO_DEG(_rad) ((_rad)*(180.0f/M_PI))

typedef union vec2{  /* Vector of 2 floats           */
	GLfloat raw[2];    /* Either 2 raw 32-bit floats   */
	struct{            /* Or a pair of x and y floats  */
		GLfloat x, y;
	};
	struct{            /* Or a pair of x and z floats  */
		GLfloat _x, z;
	};
}vec2_t;

typedef union vec3{  /* Vector of 3 floats           */
	GLfloat raw[3];    /* Either 3 raw 32-bit floats   */
	struct{            /* Or x, y, z floats            */
		GLfloat x, y, z;
	};
}vec3_t;

typedef union vec4{  /* Vector of 4 floats           */
	GLfloat raw[4];    /* Either 4 raw 32-bit floats   */
	struct{            /* Or x, y, z, w floats         */
		GLfloat x, y, z, w;
	};
}vec4_t;

typedef vec4_t quat_t;   /* Call vec4 by another name */

typedef union mat3x3{   /* 3-by-3 matrix          */
	GLfloat raw[9];       /* Either 9 raw floats    */
	GLfloat cols[3][3];   /* Or 2d array of floats  */
	struct{               /* Or struct of 9 floats  */
		Glfloat m0, m1, m2,
		        m3, m4, m5,
		        m6, m7, m8;
		};
}mat3x3_t;

typedef union mat4x4{   /* 4-by-4- matrix         */
	GLfloat raw[16];      /* Either 16 raw floats   */
	GLfloat cols[4][4];   /* Or 2d array of floats  */
	struct{               /* Or struct of 16 floats */
		GLfloat m0, m1, m2, m3,
		        m4, m5, m6, m7,
		        m8, m9, m10,m11,
		        m12,m13,m14,m15;
	};
}mat4x4_t;


/*****************************************************************************/
/* vec2                                                                      */
/*****************************************************************************/

GLfloat PFM_Vec2_Dot           (vec2_t *op1, vec2_t *op2);
void    PFM_Vec2_Add           (vec2_t *op1, vec2_t *op2,   vec2_t *out);
void    PFM_Vec2_Sub           (vec2_t *op1, vec2_t *op2,   vec2_t *out);
void    PFM_Vec2_Scale         (vec2_t *op1, GLfloat scale, vec2_t *out);
GLfloat PFM_Vec2_Len           (const vec2_t *op1);
void    PFM_Vec2_Normal        (vec2_t *op1, vec2_t *out);
void    PFM_Vec2_Dump          (vec2_t *vec, FILE *dumpfile);


/*****************************************************************************/
/* vec3                                                                      */
/*****************************************************************************/

void    PFM_Vec3_Cross         (vec3_t *a,   vec3_t *b,     vec3_t *out);
GLfloat PFM_Vec3_Dot           (vec3_t *op1, vec3_t *op2);
void    PFM_Vec3_Add           (vec3_t *op1, vec3_t *op2,   vec3_t *out);
void    PFM_Vec3_Sub           (vec3_t *op1, vec3_t *op2,   vec3_t *out);
void    PFM_Vec3_Scale         (vec3_t *op1, GLfloat scale, vec3_t *out);
GLfloat PFM_Vec3_Len           (const vec3_t *op1);
void    PFM_Vec3_Normal        (vec3_t *op1, vec3_t *out);
void    PFM_Vec3_Dump          (vec3_t *vec, FILE *dumpfile);


/*****************************************************************************/
/* vec4                                                                      */
/*****************************************************************************/

GLfloat PFM_Vec4_Dot           (vec4_t *op1, vec4_t *op2,   vec4_t *out);
void    PFM_Vec4_Add           (vec4_t *op1, vec4_t *op2,   vec4_t *out);
void    PFM_Vec4_Sub           (vec4_t *op1, vec4_t *op2,   vec4_t *out);
void    PFM_Vec4_Scale         (vec4_t *op1, GLfloat scale, vec4_t *out);
GLfloat PFM_Vec4_Len           (const vec4_t *op1);
void    PFM_Vec4_Normal        (vec4_t *op1, vec4_t *out);
void    PFM_Vec4_Dump          (vec4_t *vec, FILE *dumpfile);


/*****************************************************************************/
/* mat3x3                                                                    */
/*****************************************************************************/

void    PFM_Mat3x3_Scale       (mat3x3_t *op1, GLfloat scale, mat3x3_t *out);
void    PFM_Mat3x3_Mult3x3     (mat3x3_t *op1, mat3x3_t *op2, mat3x3_t *out);
void    PFM_Mat3x3_Mult3x1     (mat3x3_t *op1, vec3_t *op2,   vec3_t *out);
void    PFM_Mat3x3_Identity    (mat3x3_t *out);


/*****************************************************************************/
/* mat4x4                                                                    */
/*****************************************************************************/

void    PFM_Mat4x4_Scale       (mat4x4_t *op1, GLfloat scale, mat4x4_t *out);
void    PFM_Mat4x4_Mult4x4     (mat4x4_t *op1, mat4x4_t *op2, mat4x4_t *out);
void    PFM_Mat4x4_Mult4x1     (mat4x4_t *op1, vec4_t *op2,   vec4_t *out);
void    PFM_Mat4x4_Identity    (mat4x4_t *out);

void    PFM_Mat4x4_MakeScale   (GLfloat s1, GLfloat s2, GLfloat s3, mat4x4_t *out);
void    PFM_Mat4x4_MakeTrans   (GLfloat tx, GLfloat ty, GLfloat tz, mat4x4_t *out);
void    PFM_Mat4x4_MakeRotX    (GLfloat radians, mat4x4_t *out);
void    PFM_Mat4x4_MakeRotY    (GLfloat radians, mat4x4_t *out);
void    PFM_Mat4x4_MakeRotZ    (GLfloat radians, mat4x4_t *out);
void    PFM_Mat4x4_RotFromQuat (const quat_t *quat, mat4x4_t *out);
void    PFM_Mat4x4_RotFromEuler(GLfloat deg_x, GLfloat deg_y, GLfloat deg_z, mat4x4_t *out);
void    PFM_Mat4x4_Inverse     (mat4x4_t *in, mat4x4_t *out);
void    PFM_Mat4x4_Transpose   (mat4x4_t *in, mat4x4_t *out);

void    PFM_Mat4x4_MakePerspective (GLfloat fov_radians, GLfloat aspect_ratio,
                                    GLfloat z_near, GLfloat z_far, mat4x4_t *out);
void    PFM_Mat4x4_MakeOrthographic(GLfloat left, GLfloat right,
                                    GLfloat top, GLfloat bot,
                                    GLfloat near, GLfloat far, mat4x4_t *out);
void    PFM_Mat4x4_MakeLookAt      (vec3_t *camera_pos, vec3_t *target_pos,
                                    vec3_t *up_dir, mat4x4_t *out);


/*****************************************************************************/
/* quat                                                                      */
/*****************************************************************************/

void    PFM_Quat_FromRotMat (mat4x4_t *mat, quat_t *out);
void    PFM_Quat_ToEuler    (quat_t *q, float *out_roll, float *out_pitch, float *out_yaw);
void    PFM_Quat_MultQuat   (quat_t *op1, quat_t *op2, quat_t *out);
void    PFM_Quat_Normal     (quat_t *op1, quat_t *out);
void    PFM_Quat_Inverse    (quat_t *op1, quat_t *out);
GLfloat PFM_Quat_PitchDiff  (quat_t *op1, quat_t *op2);


/*****************************************************************************/
/* Other                                                                     */
/*****************************************************************************/

GLfloat PFM_BilinearInterp (GLfloat q11, GLfloat q12, GLfloat q21, GLfloat q22,
                            GLfloat x1,  GLfloat x2,  GLfloat y1,  GLfloat y2,
                            GLfloat x, GLfloat y);

#endif
