#include "sine.hpp"

float replaceCOS(int val){
	if (val==0) return 1;
	if (val==45) return 0.707;
	if (val==90) return 0.0;
	if (val==135) return -0.707;
	if (val==180) return -1;
	if (val==225) return -0.707;
	if (val==315) return 0.707;
	else return 42;
}

float replaceSIN(int val){
	if (val==0) return 0;
	if (val==45) return 0.707;
	if (val==90) return 1.0;
	if (val==135) return 0.707;
	if (val==180) return 0;
	if (val==225) return -0.707;
	if (val==315) return -0.707;
	else return 42;
}

float sin90(float x){
	float x2,p3,p2,p1,p0;
	x2 = x*x;
	p3 = - 0.0001984126f 	+ 0.000002755731f*x2;
	p2 =   0.008333333f  	+ x2*p3;
	p1 = - 0.166666666f  	+ x2*p2;
	p0 =   1 				+ x2*p1;
	float sine2 = x*p0;

	return sine2;
}

float sin180(float x){
	if (x<PIHALF){
		return sin90(x);
	}else return sin90(PI-x);

}

float sinTaylor(float x){
	if (x>PI) return -sin180(x-PI);
	else return sin180(x);
}

float cosTaylor(float x){
	float v = x+PI/2;
	if (v>=2*PI){
		v -= 2*PI;
	}
	return sinTaylor(v);
}

float30 sin90_fix(float x){
	float30 x2,p3,p2,p1,p0;
	float30 c1 = - 0.0001984126;
	float30 c2 = 0.000002755731;
	float30 c3 = 0.008333333;
	float30 c4 = - 0.166666666;

	x2 = x*x;
	p3 = c1 + c2*x2;
	p2 = c3	+ x2*p3;
	p1 = c4	+ x2*p2;
	p0 =  1 + x2*p1;
	float30 sine2 = ((float30)x) *p0;

	return sine2;
}

float30 sin180_fix(float x){
	if (x<PIHALF){
		return sin90_fix(x);
	}else return sin90_fix(PI-x);

}

float30 sinTaylor_fix(float x){
	if (x>PI) return -sin180_fix(x-PI);
	else return sin180_fix(x);
}

float30 cosTaylor_fix(float x){
	float v = x+PIHALF;
	if (v>=TWOPI){
		v -= TWOPI;
	}
	return sinTaylor_fix(v);
}

float30 cordicSin_fix(float x, int nMax){
	float30 phi = (float30) x;
	float30 z_r = 0.60725293500888;
	float30 z_i = 0;
	float30 val = (float30)1;
	for (int n =0;n<nMax;n++){
		float8 a = arctan[n];
		float30 temp1 = val>>n;
		float30 z_r_old = z_r;
		float30 z_i_old = z_i;

		if (phi>=0){
			phi -= a;
			z_r = z_r_old - z_i_old * temp1;
			z_i = z_i_old + z_r_old * temp1;

		}else{
			phi += a;

			z_r = z_r_old + z_i_old * temp1;
			z_i = z_i_old - z_r_old * temp1;
		}
	}
	return z_i;
}

float30 cordicCos_fix(float x, int nMax){
	float30 phi = (float30) x;
	float30 z_r = 0.60725293500888;
	float30 z_i = 0;
	float30 val = (float30)1.0f;
	for (int n =0;n<nMax;n++){
		float30 a = arctan[n];
		float30 temp1 = val>>n;
		float30 z_r_old = z_r;
		float30 z_i_old = z_i;

		if (phi>=0){
			phi -= a;
			z_r = z_r_old - z_i_old * temp1;
			z_i = z_i_old + z_r_old * temp1;

		}else{
			phi += a;

			z_r = z_r_old + z_i_old * temp1;
			z_i = z_i_old - z_r_old * temp1;
		}
	}
	return z_r;
}

float30 cordic360_Sin_fixed(float x, int nMax){

	if (x>=ThreeHalfPI){
		return  cordicSin_fix(x-TWOPI,nMax);

	}else if (x>PI){
		return  - cordicSin_fix(x-PI,nMax);

	}else if(x>PIHALF){
		return  -cordicSin_fix(x - PI,nMax);

	}else if(x>-PI && x<=-PIHALF){
		return -cordicSin_fix(x + PI,nMax);
	}
	return cordicSin_fix(x,nMax);
}

float30 cordic360_Cos_fixed(float x, int nMax){

	if (x>=ThreeHalfPI){
		return  cordicCos_fix(x-TWOPI,nMax);
	}else if(x>PIHALF){
		return  -cordicCos_fix(x - PI,nMax);
	}else if(x>-PI && x<=-PIHALF){
		return cordicCos_fix(x + PI,nMax);
	}
	return cordicCos_fix(x,nMax);
}

void cordic_fix(float x,int nMax,float &s,float &c){
	float30 phi = (float30) x;
	float30 z_r = 0.60725293500888;
	float30 z_i = 0;
	float30 val = (float30)1;
	for (int n =0;n<nMax;n++){
		float8 a = arctan[n];
		float30 temp1 = val>>n;
		float30 z_r_old = z_r;
		float30 z_i_old = z_i;

		//phi.is_neg();
		if (phi>=0){
			phi -= a;
			z_r = z_r_old - z_i_old * temp1;
			z_i = z_i_old + z_r_old * temp1;

		}else{
			phi += a;

			z_r = z_r_old + z_i_old * temp1;
			z_i = z_i_old - z_r_old * temp1;
		}
	}
	s = z_i.to_float();
	c = z_r.to_float();
}

void cordic360_COS_SIN_fix(float x, float &s, float &c,int nMax){
	if(x>=ThreeHalfPI){
		cordic_fix(x-TWOPI,nMax,s,c);
	}else if(x>PIHALF){
		cordic_fix(x-PI,nMax,s,c);
		s = -s;
		c = -c;
	}else if(x>-PI && x<=-PIHALF){
		cordic_fix(x+PI,nMax,s,c);
		s =-s;
		c =-c;
	}else if(x>-PIHALF && x<=PIHALF){
		cordic_fix(x,nMax,s,c);
	}
}

float cordicSine(float x,int nMax){
	float z_r = 0.60725293500888;//sin
	float z_i = 0;//cos
	for (int n =0;n<nMax;n++){
		float a = arctan_double[n];
		float temp1 = 1.0f/(float)hls::powf(2,n);
		float z_r_old = z_r;
		float z_i_old = z_i;

		if (x>=0){
			x -= a;
			z_r = z_r_old - z_i_old * temp1;
			z_i = z_i_old + z_r_old * temp1;

		}else{
			x += a;

			z_r = z_r_old + z_i_old * temp1;
			z_i = z_i_old - z_r_old * temp1;
		}
	}

	return z_i;
}

float cordicCOS(float x,int nMax){
	float z_r = 0.60725293500888;//sin
	float z_i = 0;//cos
	for (int n =0;n<nMax;n++){
		float a = arctan_double[n];
		float temp1 = 1.0f/(float)hls::powf(2,n);
		float z_r_old = z_r;
		float z_i_old = z_i;

		if (x>=0){
			x -= a;
			z_r = z_r_old - z_i_old * temp1;
			z_i = z_i_old + z_r_old * temp1;

		}else{
			x += a;

			z_r = z_r_old + z_i_old * temp1;
			z_i = z_i_old - z_r_old * temp1;
		}
	}

	return z_r;
}

float cordic360_SIN(float x, int nMax){
	if (x>=ThreeHalfPI){
		return  cordicSine(x-TWOPI,nMax);
	}else if (x>PI){
		return - cordicSine(x-PI,nMax);
	}else if(x>PIHALF){
		return -cordicSine(x - PI,nMax);
	}else if(x>-PI && x<=-PIHALF){
		return -cordicSine(x + PI,nMax);
	}
	return cordicSine(x,nMax);
}

float cordic360_COS(float x, int nMax){

	if (x>=ThreeHalfPI){
		return cordicCOS(x-TWOPI,nMax);
	}else if(x>PIHALF){
		return -cordicCOS(x - PI,nMax);
	}else if(x>-PI && x<=-PIHALF){
		return cordicCOS(x + PI,nMax);
	}
	return cordicCOS(x,nMax);
}

void cordic(float x,int nMax,float &s,float &c){
	float z_r = 0.60725293500888;//sin
	float z_i = 0;//cos
	for (int n =0;n<nMax;n++){
		float a = arctan_double[n];
		float temp1 = 1.0f/(float)hls::powf(2,n);
		float z_r_old = z_r;
		float z_i_old = z_i;

		if (x>=0){
			x -= a;
			z_r = z_r_old - z_i_old * temp1;
			z_i = z_i_old + z_r_old * temp1;

		}else{
			x += a;

			z_r = z_r_old + z_i_old * temp1;
			z_i = z_i_old - z_r_old * temp1;
		}
	}

	s = z_i;
	c = z_r;
}

void cordic360_COS_SIN(float x, float &s, float &c,int nMax){
	if(x>=ThreeHalfPI){
		cordic(x-TWOPI,nMax,s,c);
	}else if(x>PIHALF){
		cordic(x-PI,nMax,s,c);
		s = -s;
		c = -c;
	}else if(x>-PI && x<=-PIHALF){
		cordic(x+PI,nMax,s,c);
		s =-s;
		c =-c;
	}else if(x>-PIHALF && x<=PIHALF){
		cordic(x,nMax,s,c);
	}

}
