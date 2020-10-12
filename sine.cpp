#include "sine.hpp"

float replaceCOS(int val){
	if (val==0) return 1;
	if (val==45) return 0.7071;
	if (val==90) return 0.0;
	if (val==135) return -0.7071;
	if (val==180) return -1;
	if (val==225) return -0.7071;
	if (val==270) return 0;
	if (val==315) return 0.7071;
	else return 42;
}

float replaceSIN(int val){
	if (val==0) return 0;
	if (val==45) return 0.7071;
	if (val==90) return 1.0;
	if (val==135) return 0.7071;
	if (val==180) return 0;
	if (val==225) return -0.7071;
	if (val==270) return -1;
	if (val==315) return -0.7071;
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

void cordic_fix(floatArg phi,int nMax,floatSin &s,floatSin &c){
	floatSin z_r = 0.60725293500888;
	floatSin z_i = 0;
	floatSin val = 1;
	for (int n =0;n<nMax;n++){
		floatTan a = arctan[n];
		floatSin temp1 = val>>n;
		floatSin z_r_old = z_r;
		floatSin z_i_old = z_i;

		if (phi.is_neg()){
			phi += a;
			z_r = z_r_old + z_i_old * temp1;
			z_i = z_i_old - z_r_old * temp1;
		}else{
			phi -= a;
			z_r = z_r_old - z_i_old * temp1;
			z_i = z_i_old + z_r_old * temp1;
		}
	}
	s = z_i;
	c = z_r;
}

void cordic360_COS_SIN_fix(floatArg x, floatSin &s, floatSin &c,int nMax){
	if(x>=(floatArg)ThreeHalfPI){
		floatArg t = x - (floatArg)TWOPI;
		cordic_fix(t,nMax,s,c);
	}else if(x>(floatSin)PIHALF){
		floatArg t = x - (floatArg)PI;
		cordic_fix(t,nMax,s,c);
		s = -s;
		c = -c;
	}else if(x>(floatArg)-PI && x<=(floatArg)-PIHALF){
		floatArg t = x + (floatArg)PI;
		cordic_fix(t,nMax,s,c);
		s =-s;
		c =-c;
	}else if(x>(floatArg)-PIHALF && x<=(floatArg)PIHALF){
		cordic_fix(x,nMax,s,c);
	}
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
	}else if(x>=-ThreeHalfPI && x<-PI){
		cordic(x+PI,nMax,s,c);
		s = -s;
		c = -c;
	}else if (x>=-TWOPI && x<-ThreeHalfPI){
		cordic(x+TWOPI,nMax,s,c);
	}else if(x>-PIHALF && x<=PIHALF){
		cordic(x,nMax,s,c);
	}

}


