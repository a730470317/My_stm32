#ifndef __NUMERIC_ALG_H__
#define __NUMERIC_ALG_H__

#define alg_max(a,b) ((a>b) ? a : b)
#define alg_min(a,b) ((a<b) ? a : b)
#define alg_abs(a)   ((a>0)?  a:-(a))
#define agl_swap(a,b) {a=a+b; b=a-b; a=a-b;}
#define alg_swap(a,b,temp) {temp=b; b=a;a=temp;}
#define alg_limit(val,u_bound,l_bound) alg_max( l_bound, alg_min(val, u_bound))
#define alg_limit_abs(val,bound) alg_max( -alg_abs(bound), alg_min(val, alg_abs(bound)))

#endif