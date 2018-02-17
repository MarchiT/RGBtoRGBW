#include <iostream>

using namespace std;

static int32_t trim(int32_t color) {
	if (color < 0) return 0;
	else if (color > 255) return 255;
	return color;
}

static void print(int Ro, int Go, int Bo, int Wo) {
	cout << "RGBW(" << Ro << ", " << Go << ", " << Bo << ", " << Wo << ")" << endl; 
	//WRGB
	cout << "((uint32_t)" << Wo << 
		" << 24) | ((uint32_t)" << Ro << 
		" << 16) | ((uint32_t)" << Go << " << 8) | " 
		<< Bo << endl << endl;
}

static void convert(int Ri, int Gi, int Bi) {
	double tM = max(Ri, max(Gi, Bi));
	
	if (tM == 0) {
		print(0, 0, 0, 0);
		return;
	}

	//this section serves to figure out what the color with 100% hue is
	double multiplier = 255.0 / tM;
	double hR = Ri * multiplier;
	double hG = Gi * multiplier;
	double hB = Bi * multiplier;

	//this calculates the Whiteness (not strictly speaking Luminance) of the color
	double M = max(hR, max(hG, hB));
	double m = min(hR, max(hG, hB));
	double Luminance = ((M + m) - 255.0) / multiplier;

	//Calculate the output
	int Wo = (int32_t)Luminance;
	int Ro = (int32_t)(Ri - Luminance);
	int Go = (int32_t)(Gi - Luminance);
	int Bo = (int32_t)(Bi - Luminance);

	//Trim them so that they are all between 0 and 255
	Wo = trim(Wo);
	Ro = trim(Ro);
	Go = trim(Go);
	Bo = trim(Bo);

	//Print the corresponding result
	print(Ro, Go, Bo, Wo);
}

int main() {
	while(true) {

		int r, g, b;

		cout << "R: "; cin >> r;
		cout << "G: "; cin >> g;
		cout << "B: "; cin >> b;

		convert(r, g, b);
	}

	return 0;
}


