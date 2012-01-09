#include "arrow_animate2_000001.h"
#include "arrow_animate2_000002.h"
#include "arrow_animate2_000003.h"
#include "arrow_animate2_000004.h"
#include "arrow_animate2_000005.h"
#include "arrow_animate2_000006.h"
#include "arrow_animate2_000007.h"
#include "arrow_animate2_000008.h"
#include "arrow_animate2_000009.h"
#include "arrow_animate2_000010.h"
#include "arrow_animate2_000011.h"
#include "arrow_animate2_000012.h"
#include "arrow_animate2_000013.h"
#include "arrow_animate2_000014.h"
#include "arrow_animate2_000015.h"
#include "arrow_animate2_000016.h"
#include "arrow_animate2_000017.h"
#include "arrow_animate2_000018.h"
#include "arrow_animate2_000019.h"
#include "arrow_animate2_000020.h"
#include "arrow_animate2_000021.h"
#include "arrow_animate2_000022.h"
#include "arrow_animate2_000023.h"
#include "arrow_animate2_000024.h"
#include "arrow_animate2_000025.h"
#include "arrow_animate2_000026.h"
#include "arrow_animate2_000027.h"
#include "arrow_animate2_000028.h"
#include "arrow_animate2_000029.h"
#include "arrow_animate2_000030.h"
#include "arrow_animate2_000031.h"
#include "arrow_animate2_000032.h"
#include "arrow_animate2_000033.h"
#include "arrow_animate2_000034.h"
#include "arrow_animate2_000035.h"
#include "arrow_animate2_000036.h"
#include "arrow_animate2_000037.h"
#include "arrow_animate2_000038.h"
#include "arrow_animate2_000039.h"
#include "arrow_animate2_000040.h"
#include "arrow_animate2_000041.h"
#include "arrow_animate2_000042.h"
#include "arrow_animate2_000043.h"
#include "arrow_animate2_000044.h"
#include "arrow_animate2_000045.h"
#include "arrow_animate2_000046.h"
#include "arrow_animate2_000047.h"
#include "arrow_animate2_000048.h"

#include "headless_horse3_000001.h"
#include "headless_horse3_000002.h"
#include "headless_horse3_000003.h"
#include "headless_horse3_000004.h"
#include "headless_horse3_000005.h"
#include "headless_horse3_000006.h"
#include "headless_horse3_000007.h"
#include "headless_horse3_000008.h"
#include "headless_horse3_000009.h"
#include "headless_horse3_000010.h"
#include "headless_horse3_000011.h"
#include "headless_horse3_000012.h"
#include "headless_horse3_000013.h"
#include "headless_horse3_000014.h"
#include "headless_horse3_000015.h"
#include "headless_horse3_000016.h"
#include "headless_horse3_000017.h"
#include "headless_horse3_000018.h"
#include "headless_horse3_000019.h"
#include "headless_horse3_000020.h"
#include "headless_horse3_000021.h"
#include "headless_horse3_000022.h"
#include "headless_horse3_000023.h"
#include "headless_horse3_000024.h"
#include "headless_horse3_000025.h"
#include "headless_horse3_000026.h"
#include "headless_horse3_000027.h"
#include "headless_horse3_000028.h"
#include "headless_horse3_000029.h"
#include "headless_horse3_000030.h"
#include "headless_horse3_000031.h"
#include "headless_horse3_000032.h"
#include "headless_horse3_000033.h"
#include "headless_horse3_000034.h"
#include "headless_horse3_000035.h"
#include "headless_horse3_000036.h"
#include "headless_horse3_000037.h"
#include "headless_horse3_000038.h"
#include "headless_horse3_000039.h"
#include "headless_horse3_000040.h"
#include "headless_horse3_000041.h"
#include "headless_horse3_000042.h"
#include "headless_horse3_000043.h"
#include "headless_horse3_000044.h"
#include "headless_horse3_000045.h"
#include "headless_horse3_000046.h"
#include "headless_horse3_000047.h"
#include "headless_horse3_000048.h"


struct graphics_arrays {

unsigned int * NumVerts;
float * Verts;
float * Normals;
float * TexCoords;

};

struct graphics_arrays get_graphics_stats (int index, int type) {
	struct graphics_arrays temp_struct;
	//if (strcmp (type,"arrow") == 1){
	if (!type) {
		if (index == 1){
			temp_struct.NumVerts = &arrow_animate2_000001NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000001Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000001Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000001TexCoords;
		}
		else if (index == 2){
			temp_struct.NumVerts = &arrow_animate2_000002NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000002Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000002Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000002TexCoords;
		}
		else if (index == 3){
			temp_struct.NumVerts = &arrow_animate2_000003NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000003Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000003Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000003TexCoords;
		}
		else if (index == 4){
			temp_struct.NumVerts = &arrow_animate2_000004NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000004Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000004Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000004TexCoords;
		}
		else if (index == 5){
			temp_struct.NumVerts = &arrow_animate2_000005NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000005Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000005Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000005TexCoords;
		}
		else if (index == 6){
			temp_struct.NumVerts = &arrow_animate2_000006NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000006Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000006Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000006TexCoords;
		}
		else if (index == 7){
			temp_struct.NumVerts = &arrow_animate2_000007NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000007Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000007Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000007TexCoords;
		}
		else if (index == 8){
			temp_struct.NumVerts = &arrow_animate2_000008NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000008Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000008Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000008TexCoords;
		}
		else if (index == 9){
			temp_struct.NumVerts = &arrow_animate2_000009NumVerts;
			temp_struct.Verts = (float *) &arrow_animate2_000009Verts;
			temp_struct.Normals = (float *) &arrow_animate2_000009Normals;
			temp_struct.TexCoords = (float *) &arrow_animate2_000009TexCoords;
		}
		else if (index == 10){
		  temp_struct.NumVerts = &arrow_animate2_000010NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000010Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000010Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000010TexCoords;
		}
		else if (index == 11){
		  temp_struct.NumVerts = &arrow_animate2_000011NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000011Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000011Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000011TexCoords;
		}
		else if (index == 12){
		  temp_struct.NumVerts = &arrow_animate2_000012NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000012Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000012Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000012TexCoords;
		}
		else if (index == 13){
		  temp_struct.NumVerts = &arrow_animate2_000013NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000013Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000013Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000013TexCoords;
		}
		else if (index == 14){
		  temp_struct.NumVerts = &arrow_animate2_000014NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000014Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000014Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000014TexCoords;
		}
		else if (index == 15){
		  temp_struct.NumVerts = &arrow_animate2_000015NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000015Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000015Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000015TexCoords;
		}
		else if (index == 16){
		  temp_struct.NumVerts = &arrow_animate2_000016NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000016Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000016Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000016TexCoords;
		}
		else if (index == 17){
		  temp_struct.NumVerts = &arrow_animate2_000017NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000017Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000017Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000017TexCoords;
		}
		else if (index == 18){
		  temp_struct.NumVerts = &arrow_animate2_000018NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000018Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000018Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000018TexCoords;
		}
		else if (index == 19){
		  temp_struct.NumVerts = &arrow_animate2_000019NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000019Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000019Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000019TexCoords;
		}
		else if (index == 20){
		  temp_struct.NumVerts = &arrow_animate2_000020NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000020Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000020Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000020TexCoords;
		}
		else if (index == 21){
		  temp_struct.NumVerts = &arrow_animate2_000021NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000021Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000021Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000021TexCoords;
		}
		else if (index == 22){
		  temp_struct.NumVerts = &arrow_animate2_000022NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000022Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000022Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000022TexCoords;
		}
		else if (index == 23){
		  temp_struct.NumVerts = &arrow_animate2_000023NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000023Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000023Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000023TexCoords;
		}
		else if (index == 24){
		  temp_struct.NumVerts = &arrow_animate2_000024NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000024Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000024Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000024TexCoords;
		}
		else if (index == 25){
		  temp_struct.NumVerts = &arrow_animate2_000025NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000025Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000025Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000025TexCoords;
		}
		else if (index == 26){
		  temp_struct.NumVerts = &arrow_animate2_000026NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000026Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000026Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000026TexCoords;
		}
		else if (index == 27){
		  temp_struct.NumVerts = &arrow_animate2_000027NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000027Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000027Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000027TexCoords;
		}
		else if (index == 28){
		  temp_struct.NumVerts = &arrow_animate2_000028NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000028Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000028Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000028TexCoords;
		}
		else if (index == 29){
		  temp_struct.NumVerts = &arrow_animate2_000029NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000029Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000029Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000029TexCoords;
		}
		else if (index == 30){
		  temp_struct.NumVerts = &arrow_animate2_000030NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000030Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000030Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000030TexCoords;
		}
		else if (index == 31){
		  temp_struct.NumVerts = &arrow_animate2_000031NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000031Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000031Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000031TexCoords;
		}
		else if (index == 32){
		  temp_struct.NumVerts = &arrow_animate2_000032NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000032Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000032Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000032TexCoords;
		}
		else if (index == 33){
		  temp_struct.NumVerts = &arrow_animate2_000033NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000033Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000033Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000033TexCoords;
		}
		else if (index == 34){
		  temp_struct.NumVerts = &arrow_animate2_000034NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000034Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000034Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000034TexCoords;
		}
		else if (index == 35){
		  temp_struct.NumVerts = &arrow_animate2_000035NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000035Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000035Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000035TexCoords;
		}
		else if (index == 36){
		  temp_struct.NumVerts = &arrow_animate2_000036NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000036Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000036Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000036TexCoords;
		}
		else if (index == 37){
		  temp_struct.NumVerts = &arrow_animate2_000037NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000037Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000037Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000037TexCoords;
		}
		else if (index == 38){
		  temp_struct.NumVerts = &arrow_animate2_000038NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000038Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000038Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000038TexCoords;
		}
		else if (index == 39){
		  temp_struct.NumVerts = &arrow_animate2_000039NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000039Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000039Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000039TexCoords;
		}
		else if (index == 40){
		  temp_struct.NumVerts = &arrow_animate2_000040NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000040Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000040Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000040TexCoords;
		}
		else if (index == 41){
		  temp_struct.NumVerts = &arrow_animate2_000041NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000041Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000041Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000041TexCoords;
		}
		else if (index == 42){
		  temp_struct.NumVerts = &arrow_animate2_000042NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000042Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000042Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000042TexCoords;
		}
		else if (index == 43){
		  temp_struct.NumVerts = &arrow_animate2_000043NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000043Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000043Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000043TexCoords;
		}
		else if (index == 44){
		  temp_struct.NumVerts = &arrow_animate2_000044NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000044Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000044Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000044TexCoords;
		}
		else if (index == 45){
		  temp_struct.NumVerts = &arrow_animate2_000045NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000045Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000045Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000045TexCoords;
		}
		else if (index == 46){
		  temp_struct.NumVerts = &arrow_animate2_000046NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000046Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000046Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000046TexCoords;
		}
		else if (index == 47){
		  temp_struct.NumVerts = &arrow_animate2_000047NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000047Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000047Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000047TexCoords;
		}
		else if (index == 48){
		  temp_struct.NumVerts = &arrow_animate2_000048NumVerts;
		  temp_struct.Verts = (float *) &arrow_animate2_000048Verts;
		  temp_struct.Normals = (float *) &arrow_animate2_000048Normals;
		  temp_struct.TexCoords = (float *) &arrow_animate2_000048TexCoords;
		}
	}
	//else if (strcmp (type,"horse") == 1){
	else if (type){
		if (index == 1){
			temp_struct.NumVerts = &headless_horse3_000001NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000001Verts;
			temp_struct.Normals = (float *) &headless_horse3_000001Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000001TexCoords;
		}
		else if (index == 2){
			temp_struct.NumVerts = &headless_horse3_000002NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000002Verts;
			temp_struct.Normals = (float *) &headless_horse3_000002Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000002TexCoords;
		}
		else if (index == 3){
			temp_struct.NumVerts = &headless_horse3_000003NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000003Verts;
			temp_struct.Normals = (float *) &headless_horse3_000003Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000003TexCoords;
		}
		else if (index == 4){
			temp_struct.NumVerts = &headless_horse3_000004NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000004Verts;
			temp_struct.Normals = (float *) &headless_horse3_000004Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000004TexCoords;
		}
		else if (index == 5){
			temp_struct.NumVerts = &headless_horse3_000005NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000005Verts;
			temp_struct.Normals = (float *) &headless_horse3_000005Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000005TexCoords;
		}
		else if (index == 6){
			temp_struct.NumVerts = &headless_horse3_000006NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000006Verts;
			temp_struct.Normals = (float *) &headless_horse3_000006Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000006TexCoords;
		}
		else if (index == 7){
			temp_struct.NumVerts = &headless_horse3_000007NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000007Verts;
			temp_struct.Normals = (float *) &headless_horse3_000007Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000007TexCoords;
		}
		else if (index == 8){
			temp_struct.NumVerts = &headless_horse3_000008NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000008Verts;
			temp_struct.Normals = (float *) &headless_horse3_000008Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000008TexCoords;
		}
		else if (index == 9){
			temp_struct.NumVerts = &headless_horse3_000009NumVerts;
			temp_struct.Verts = (float *) &headless_horse3_000009Verts;
			temp_struct.Normals = (float *) &headless_horse3_000009Normals;
			temp_struct.TexCoords = (float *) &headless_horse3_000009TexCoords;
		}
		else if (index == 10){
		  temp_struct.NumVerts = &headless_horse3_000010NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000010Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000010Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000010TexCoords;
		}
		else if (index == 11){
		  temp_struct.NumVerts = &headless_horse3_000011NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000011Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000011Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000011TexCoords;
		}
		else if (index == 12){
		  temp_struct.NumVerts = &headless_horse3_000012NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000012Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000012Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000012TexCoords;
		}
		else if (index == 13){
		  temp_struct.NumVerts = &headless_horse3_000013NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000013Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000013Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000013TexCoords;
		}
		else if (index == 14){
		  temp_struct.NumVerts = &headless_horse3_000014NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000014Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000014Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000014TexCoords;
		}
		else if (index == 15){
		  temp_struct.NumVerts = &headless_horse3_000015NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000015Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000015Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000015TexCoords;
		}
		else if (index == 16){
		  temp_struct.NumVerts = &headless_horse3_000016NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000016Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000016Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000016TexCoords;
		}
		else if (index == 17){
		  temp_struct.NumVerts = &headless_horse3_000017NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000017Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000017Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000017TexCoords;
		}
		else if (index == 18){
		  temp_struct.NumVerts = &headless_horse3_000018NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000018Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000018Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000018TexCoords;
		}
		else if (index == 19){
		  temp_struct.NumVerts = &headless_horse3_000019NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000019Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000019Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000019TexCoords;
		}
		else if (index == 20){
		  temp_struct.NumVerts = &headless_horse3_000020NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000020Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000020Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000020TexCoords;
		}
		else if (index == 21){
		  temp_struct.NumVerts = &headless_horse3_000021NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000021Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000021Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000021TexCoords;
		}
		else if (index == 22){
		  temp_struct.NumVerts = &headless_horse3_000022NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000022Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000022Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000022TexCoords;
		}
		else if (index == 23){
		  temp_struct.NumVerts = &headless_horse3_000023NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000023Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000023Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000023TexCoords;
		}
		else if (index == 24){
		  temp_struct.NumVerts = &headless_horse3_000024NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000024Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000024Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000024TexCoords;
		}
		else if (index == 25){
		  temp_struct.NumVerts = &headless_horse3_000025NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000025Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000025Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000025TexCoords;
		}
		else if (index == 26){
		  temp_struct.NumVerts = &headless_horse3_000026NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000026Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000026Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000026TexCoords;
		}
		else if (index == 27){
		  temp_struct.NumVerts = &headless_horse3_000027NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000027Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000027Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000027TexCoords;
		}
		else if (index == 28){
		  temp_struct.NumVerts = &headless_horse3_000028NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000028Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000028Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000028TexCoords;
		}
		else if (index == 29){
		  temp_struct.NumVerts = &headless_horse3_000029NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000029Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000029Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000029TexCoords;
		}
		else if (index == 30){
		  temp_struct.NumVerts = &headless_horse3_000030NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000030Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000030Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000030TexCoords;
		}
		else if (index == 31){
		  temp_struct.NumVerts = &headless_horse3_000031NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000031Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000031Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000031TexCoords;
		}
		else if (index == 32){
		  temp_struct.NumVerts = &headless_horse3_000032NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000032Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000032Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000032TexCoords;
		}
		else if (index == 33){
		  temp_struct.NumVerts = &headless_horse3_000033NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000033Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000033Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000033TexCoords;
		}
		else if (index == 34){
		  temp_struct.NumVerts = &headless_horse3_000034NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000034Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000034Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000034TexCoords;
		}
		else if (index == 35){
		  temp_struct.NumVerts = &headless_horse3_000035NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000035Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000035Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000035TexCoords;
		}
		else if (index == 36){
		  temp_struct.NumVerts = &headless_horse3_000036NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000036Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000036Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000036TexCoords;
		}
		else if (index == 37){
		  temp_struct.NumVerts = &headless_horse3_000037NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000037Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000037Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000037TexCoords;
		}
		else if (index == 38){
		  temp_struct.NumVerts = &headless_horse3_000038NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000038Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000038Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000038TexCoords;
		}
		else if (index == 39){
		  temp_struct.NumVerts = &headless_horse3_000039NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000039Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000039Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000039TexCoords;
		}
		else if (index == 40){
		  temp_struct.NumVerts = &headless_horse3_000040NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000040Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000040Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000040TexCoords;
		}
		else if (index == 41){
		  temp_struct.NumVerts = &headless_horse3_000041NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000041Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000041Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000041TexCoords;
		}
		else if (index == 42){
		  temp_struct.NumVerts = &headless_horse3_000042NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000042Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000042Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000042TexCoords;
		}
		else if (index == 43){
		  temp_struct.NumVerts = &headless_horse3_000043NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000043Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000043Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000043TexCoords;
		}
		else if (index == 44){
		  temp_struct.NumVerts = &headless_horse3_000044NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000044Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000044Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000044TexCoords;
		}
		else if (index == 45){
		  temp_struct.NumVerts = &headless_horse3_000045NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000045Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000045Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000045TexCoords;
		}
		else if (index == 46){
		  temp_struct.NumVerts = &headless_horse3_000046NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000046Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000046Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000046TexCoords;
		}
		else if (index == 47){
		  temp_struct.NumVerts = &headless_horse3_000047NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000047Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000047Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000047TexCoords;
		}
		else if (index == 48){
		  temp_struct.NumVerts = &headless_horse3_000048NumVerts;
		  temp_struct.Verts = (float *) &headless_horse3_000048Verts;
		  temp_struct.Normals = (float *) &headless_horse3_000048Normals;
		  temp_struct.TexCoords = (float *) &headless_horse3_000048TexCoords;
		}
		
	}
	return temp_struct;
} 