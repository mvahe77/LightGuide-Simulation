{
#include<iomanip>
  cout.setf( ios::fixed );

  double D = 141.6 - 5.4;
  double d =   8.0;
  double S =  50.0;

  double R = 0.5 * ( (D*D + S*S)/(2*S) -d );

  double ASIN = D/(2*R+d);
  double ACOS = sqrt( 1 - ASIN*ASIN );

  double angle = acos( ACOS ) * TMath::RadToDeg();
  double zpos1234 =  -5.4;
  double zpos5678 = -141.6;

  cout << "D = " << D << endl;
  cout << "R   = " << setprecision(16) << R << endl
       << "R+d = " << setprecision(16) << R+d << endl << endl
       << "    ang = " << angle << endl
       << " 90-ang   " <<  90-angle << endl
       << "180-ang   " << 180-angle << endl
       << "270-ang   " << 270-angle << endl
       << endl;

  cout << "D = " << R*ASIN + (R+d)*ASIN << endl;
  cout << "LG Xpos1 = " << endl;

  cout << 
    "<tube name = \"sSeg1\"   rmin=\"" << setprecision(16) << R << "\"     rmax=\"" << R+d 
       << "\"      z=\"35.5\" deltaphi=\""<<angle<<"\" startphi=\""<< 90-angle<<"\"  aunit=\"deg\" lunit= \"mm\"/> "
       << endl;
  cout << "<position name=\"posSeg1\" x=\"53.25\" y=\"-"<< R<<"\" z=\""<< setprecision(1) << zpos1234 <<"\"/> "<< endl;

  cout << 
    "<tube name = \"sSeg5\"   rmin=\"" << setprecision(16) << R << "\"     rmax=\"" << R+d 
       << "\"      z=\"35.5\" deltaphi=\""<<angle<<"\" startphi=\""<< 270-angle<<"\"  aunit=\"deg\" lunit= \"mm\"/> "
       << endl;
  cout << "<position name=\"posSeg5\" x=\"53.25\" y=\""<< R + d -S <<"\" z=\""<< setprecision(1) << zpos5678<<"\"/> "<< endl;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   S =  42.0;

   R = 0.5 * ( (D*D + S*S)/(2*S) -d );

   ASIN = D/(2*R+d);
   ACOS = sqrt( 1 - ASIN*ASIN );

   angle = acos( ACOS ) * TMath::RadToDeg();

  cout << 
    "<tube name = \"sSeg2\"   rmin=\"" << setprecision(16) << R << "\"     rmax=\"" << R+d 
       << "\"      z=\"35.5\" deltaphi=\""<<angle<<"\" startphi=\""<< 90-angle<<"\"  aunit=\"deg\" lunit= \"mm\"/> "
       << endl;
  cout << "<position name=\"posSeg2\" x=\"17.75\" y=\"-"<< R<<"\" z=\""<< setprecision(1) << zpos1234 <<"\"/> "<< endl;

  cout << 
    "<tube name = \"sSeg6\"   rmin=\"" << setprecision(16) << R << "\"     rmax=\"" << R+d 
       << "\"      z=\"35.5\" deltaphi=\""<<angle<<"\" startphi=\""<< 270-angle<<"\"  aunit=\"deg\" lunit= \"mm\"/> "
       << endl;
  cout << "<position name=\"posSeg6\" x=\"17.75\" y=\""<< R + d -S <<"\" z=\""<< setprecision(1) << zpos5678<<"\"/> "<< endl;
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   S =  34.0;

   R = 0.5 * ( (D*D + S*S)/(2*S) -d );

   ASIN = D/(2*R+d);
   ACOS = sqrt( 1 - ASIN*ASIN );

   angle = acos( ACOS ) * TMath::RadToDeg();

  cout << 
    "<tube name = \"sSeg3\"   rmin=\"" << setprecision(16) << R << "\"     rmax=\"" << R+d 
       << "\"      z=\"35.5\" deltaphi=\""<<angle<<"\" startphi=\""<< 90-angle<<"\"  aunit=\"deg\" lunit= \"mm\"/> "
       << endl;
  cout << "<position name=\"posSeg3\" x=\"-17.75\" y=\"-"<< R<<"\" z=\""<< setprecision(1) << zpos1234 <<"\"/> "<< endl;

  cout << 
    "<tube name = \"sSeg7\"   rmin=\"" << setprecision(16) << R << "\"     rmax=\"" << R+d 
       << "\"      z=\"35.5\" deltaphi=\""<<angle<<"\" startphi=\""<< 270-angle<<"\"  aunit=\"deg\" lunit= \"mm\"/> "
       << endl;
  cout << "<position name=\"posSeg7\" x=\"-17.75\" y=\""<< R + d -S <<"\" z=\""<< setprecision(1) << zpos5678<<"\"/> "<< endl;
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   S =  26.0;

   R = 0.5 * ( (D*D + S*S)/(2*S) -d );

   ASIN = D/(2*R+d);
   ACOS = sqrt( 1 - ASIN*ASIN );

   angle = acos( ACOS ) * TMath::RadToDeg();


  cout << 
    "<tube name = \"sSeg4\"   rmin=\"" << setprecision(16) << R << "\"     rmax=\"" << R+d 
       << "\"      z=\"35.5\" deltaphi=\""<<angle<<"\" startphi=\""<< 90-angle<<"\"  aunit=\"deg\" lunit= \"mm\"/> "
       << endl;

  cout << "<position name=\"posSeg4\" x=\"-53.25\" y=\"-"<< R<<"\" z=\""<< setprecision(1) << zpos1234 <<"\"/> "<< endl; 

  cout << 
    "<tube name = \"sSeg8\"   rmin=\"" << setprecision(16) << R << "\"     rmax=\"" << R+d 
       << "\"      z=\"35.5\" deltaphi=\""<<angle<<"\" startphi=\""<< 270-angle<<"\"  aunit=\"deg\" lunit= \"mm\"/> "
       << endl;
  cout << "<position name=\"posSeg8\" x=\"-53.25\" y=\""<< R + d -S <<"\" z=\""<< setprecision(1) << zpos5678 << "\"/> "<< endl;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}
