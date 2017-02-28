{
#include<iomanip>
  cout.setf( ios::fixed );

  double D = 411.316144099999974-141.6;
  double d = 35.5;
  
  double R = (D*D - 3.0/4.0 * d*d)/(2*d);
  
  double ACOS = ( R + d/4.0 ) / ( R + d/2.0 );
  double ASIN = sqrt(1-ACOS*ACOS);

  double angle = acos( ACOS ) * TMath::RadToDeg();

  cout << "D = " << D << endl;
  cout << "R   = " << setprecision(16) << R 
       << "R+d = " << setprecision(16) << R+d 

       << " angle = " << angle <<endl;

  cout << "D = " << R*ASIN + (R+d)*ASIN << endl;
  cout << "LG Xpos1 = " << endl;


  R = (D*D - 3.0/4.0 * d*d)/(6*d);
  ACOS = ( R - d/4.0 ) / ( R + d/2.0 );  
  ASIN = sqrt(1-ACOS*ACOS);

  angle = acos( ACOS ) * TMath::RadToDeg();

  cout << "D = " << D << endl;
  cout << "R   = " << setprecision(16) << R 
       << " R+d = " << setprecision(16) << R+d 

       << " angle = " << angle <<endl;

  cout << "D = " << R*ASIN + (R+d)*ASIN << endl;
  cout << "LG Xpos1 = " << endl;



}
