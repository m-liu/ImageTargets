
#include "tower.h"
#include "snowball.h"
#include "igloo.h"
#include "spaceship.h"
#include "tank.h"

#include "arrow_new_000001.h"
#include "arrow_new_000002.h"
#include "arrow_new_000003.h"
#include "arrow_new_000004.h"
#include "arrow_new_000005.h"
#include "arrow_new_000006.h"
#include "arrow_new_000007.h"
#include "arrow_new_000008.h"
#include "arrow_new_000009.h"
#include "arrow_new_000010.h"
#include "arrow_new_000011.h"
#include "arrow_new_000012.h"
#include "arrow_new_000013.h"
#include "arrow_new_000014.h"
#include "arrow_new_000015.h"
#include "arrow_new_000016.h"
#include "arrow_new_000017.h"
#include "arrow_new_000018.h"
#include "arrow_new_000019.h"
#include "arrow_new_000020.h"
#include "arrow_new_000021.h"
#include "arrow_new_000022.h"
#include "arrow_new_000023.h"
#include "arrow_new_000024.h"
/*
#include "arrow_new_000025.h"
#include "arrow_new_000026.h"
#include "arrow_new_000027.h"
#include "arrow_new_000028.h"
#include "arrow_new_000029.h"
#include "arrow_new_000030.h"
#include "arrow_new_000031.h"
#include "arrow_new_000032.h"
#include "arrow_new_000033.h"
#include "arrow_new_000034.h"
#include "arrow_new_000035.h"
#include "arrow_new_000036.h"
#include "arrow_new_000037.h"
#include "arrow_new_000038.h"
#include "arrow_new_000039.h"
#include "arrow_new_000040.h"
#include "arrow_new_000041.h"
#include "arrow_new_000042.h"
#include "arrow_new_000043.h"
#include "arrow_new_000044.h"
#include "arrow_new_000045.h"
#include "arrow_new_000046.h"
#include "arrow_new_000047.h"
#include "arrow_new_000048.h"
*/

#include "cow_000001.h"
#include "cow_000002.h"
#include "cow_000003.h"
#include "cow_000004.h"
#include "cow_000005.h"
#include "cow_000006.h"
#include "cow_000007.h"
#include "cow_000008.h"
#include "cow_000009.h"
#include "cow_000010.h"
#include "cow_000011.h"
#include "cow_000012.h"
#include "cow_000013.h"
#include "cow_000014.h"
#include "cow_000015.h"
#include "cow_000016.h"
#include "cow_000017.h"
#include "cow_000018.h"
#include "cow_000019.h"
#include "cow_000020.h"
#include "cow_000021.h"
#include "cow_000022.h"
#include "cow_000023.h"
#include "cow_000024.h"
#include "cow_000025.h"
#include "cow_000026.h"
#include "cow_000027.h"
#include "cow_000028.h"
#include "cow_000029.h"
#include "cow_000030.h"
#include "cow_000031.h"
#include "cow_000032.h"
#include "cow_000033.h"
#include "cow_000034.h"
#include "cow_000035.h"
#include "cow_000036.h"
#include "cow_000037.h"
#include "cow_000038.h"
#include "cow_000039.h"
#include "cow_000040.h"
#include "cow_000041.h"
#include "cow_000042.h"
#include "cow_000043.h"
#include "cow_000044.h"
#include "cow_000045.h"
#include "cow_000046.h"
#include "cow_000047.h"
#include "cow_000048.h"


#include "zombie_000001.h"
#include "zombie_000002.h"
#include "zombie_000003.h"
#include "zombie_000004.h"
#include "zombie_000005.h"
#include "zombie_000006.h"
#include "zombie_000007.h"
#include "zombie_000008.h"
#include "zombie_000009.h"
#include "zombie_000010.h"
#include "zombie_000011.h"
#include "zombie_000012.h"
#include "zombie_000013.h"
#include "zombie_000014.h"
#include "zombie_000015.h"
#include "zombie_000016.h"
#include "zombie_000017.h"
#include "zombie_000018.h"
#include "zombie_000019.h"
#include "zombie_000020.h"
#include "zombie_000021.h"
#include "zombie_000022.h"
#include "zombie_000023.h"
#include "zombie_000024.h"
#include "zombie_000025.h"
#include "zombie_000026.h"
#include "zombie_000027.h"
#include "zombie_000028.h"
#include "zombie_000029.h"
#include "zombie_000030.h"
#include "zombie_000031.h"
#include "zombie_000032.h"
#include "zombie_000033.h"
#include "zombie_000034.h"
#include "zombie_000035.h"
#include "zombie_000036.h"
#include "zombie_000037.h"
#include "zombie_000038.h"
#include "zombie_000039.h"
#include "zombie_000040.h"
#include "zombie_000041.h"
#include "zombie_000042.h"
#include "zombie_000043.h"
#include "zombie_000044.h"
#include "zombie_000045.h"
#include "zombie_000046.h"
#include "zombie_000047.h"
#include "zombie_000048.h"


struct graphics_arrays {

unsigned int * NumVerts;
float * Verts;
float * Normals;
float * TexCoords;

};

struct graphics_arrays get_graphics_stats (int index, int type) {
	struct graphics_arrays temp_struct;
	//if (strcmp (type,"arrow") == 1){
	if (type == 0) {
		if (index == 1){
			temp_struct.NumVerts = &arrow_new_000001NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000001Verts;
			temp_struct.Normals = (float *) &arrow_new_000001Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000001TexCoords;
		}
		else if (index == 2){
			temp_struct.NumVerts = &arrow_new_000002NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000002Verts;
			temp_struct.Normals = (float *) &arrow_new_000002Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000002TexCoords;
		}
		else if (index == 3){
			temp_struct.NumVerts = &arrow_new_000003NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000003Verts;
			temp_struct.Normals = (float *) &arrow_new_000003Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000003TexCoords;
		}
		else if (index == 4){
			temp_struct.NumVerts = &arrow_new_000004NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000004Verts;
			temp_struct.Normals = (float *) &arrow_new_000004Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000004TexCoords;
		}
		else if (index == 5){
			temp_struct.NumVerts = &arrow_new_000005NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000005Verts;
			temp_struct.Normals = (float *) &arrow_new_000005Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000005TexCoords;
		}
		else if (index == 6){
			temp_struct.NumVerts = &arrow_new_000006NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000006Verts;
			temp_struct.Normals = (float *) &arrow_new_000006Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000006TexCoords;
		}
		else if (index == 7){
			temp_struct.NumVerts = &arrow_new_000007NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000007Verts;
			temp_struct.Normals = (float *) &arrow_new_000007Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000007TexCoords;
		}
		else if (index == 8){
			temp_struct.NumVerts = &arrow_new_000008NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000008Verts;
			temp_struct.Normals = (float *) &arrow_new_000008Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000008TexCoords;
		}
		else if (index == 9){
			temp_struct.NumVerts = &arrow_new_000009NumVerts;
			temp_struct.Verts = (float *) &arrow_new_000009Verts;
			temp_struct.Normals = (float *) &arrow_new_000009Normals;
			temp_struct.TexCoords = (float *) &arrow_new_000009TexCoords;
		}
		else if (index == 10){
		  temp_struct.NumVerts = &arrow_new_000010NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000010Verts;
		  temp_struct.Normals = (float *) &arrow_new_000010Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000010TexCoords;
		}
		else if (index == 11){
		  temp_struct.NumVerts = &arrow_new_000011NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000011Verts;
		  temp_struct.Normals = (float *) &arrow_new_000011Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000011TexCoords;
		}
		else if (index == 12){
		  temp_struct.NumVerts = &arrow_new_000012NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000012Verts;
		  temp_struct.Normals = (float *) &arrow_new_000012Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000012TexCoords;
		}
		else if (index == 13){
		  temp_struct.NumVerts = &arrow_new_000013NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000013Verts;
		  temp_struct.Normals = (float *) &arrow_new_000013Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000013TexCoords;
		}
		else if (index == 14){
		  temp_struct.NumVerts = &arrow_new_000014NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000014Verts;
		  temp_struct.Normals = (float *) &arrow_new_000014Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000014TexCoords;
		}
		else if (index == 15){
		  temp_struct.NumVerts = &arrow_new_000015NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000015Verts;
		  temp_struct.Normals = (float *) &arrow_new_000015Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000015TexCoords;
		}
		else if (index == 16){
		  temp_struct.NumVerts = &arrow_new_000016NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000016Verts;
		  temp_struct.Normals = (float *) &arrow_new_000016Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000016TexCoords;
		}
		else if (index == 17){
		  temp_struct.NumVerts = &arrow_new_000017NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000017Verts;
		  temp_struct.Normals = (float *) &arrow_new_000017Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000017TexCoords;
		}
		else if (index == 18){
		  temp_struct.NumVerts = &arrow_new_000018NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000018Verts;
		  temp_struct.Normals = (float *) &arrow_new_000018Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000018TexCoords;
		}
		else if (index == 19){
		  temp_struct.NumVerts = &arrow_new_000019NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000019Verts;
		  temp_struct.Normals = (float *) &arrow_new_000019Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000019TexCoords;
		}
		else if (index == 20){
		  temp_struct.NumVerts = &arrow_new_000020NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000020Verts;
		  temp_struct.Normals = (float *) &arrow_new_000020Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000020TexCoords;
		}
		else if (index == 21){
		  temp_struct.NumVerts = &arrow_new_000021NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000021Verts;
		  temp_struct.Normals = (float *) &arrow_new_000021Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000021TexCoords;
		}
		else if (index == 22){
		  temp_struct.NumVerts = &arrow_new_000022NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000022Verts;
		  temp_struct.Normals = (float *) &arrow_new_000022Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000022TexCoords;
		}
		else if (index == 23){
		  temp_struct.NumVerts = &arrow_new_000023NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000023Verts;
		  temp_struct.Normals = (float *) &arrow_new_000023Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000023TexCoords;
		}
		else if (index == 24){
		  temp_struct.NumVerts = &arrow_new_000024NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000024Verts;
		  temp_struct.Normals = (float *) &arrow_new_000024Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000024TexCoords;
		}
		/*
		else if (index == 25){
		  temp_struct.NumVerts = &arrow_new_000025NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000025Verts;
		  temp_struct.Normals = (float *) &arrow_new_000025Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000025TexCoords;
		}
		else if (index == 26){
		  temp_struct.NumVerts = &arrow_new_000026NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000026Verts;
		  temp_struct.Normals = (float *) &arrow_new_000026Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000026TexCoords;
		}
		else if (index == 27){
		  temp_struct.NumVerts = &arrow_new_000027NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000027Verts;
		  temp_struct.Normals = (float *) &arrow_new_000027Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000027TexCoords;
		}
		else if (index == 28){
		  temp_struct.NumVerts = &arrow_new_000028NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000028Verts;
		  temp_struct.Normals = (float *) &arrow_new_000028Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000028TexCoords;
		}
		else if (index == 29){
		  temp_struct.NumVerts = &arrow_new_000029NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000029Verts;
		  temp_struct.Normals = (float *) &arrow_new_000029Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000029TexCoords;
		}
		else if (index == 30){
		  temp_struct.NumVerts = &arrow_new_000030NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000030Verts;
		  temp_struct.Normals = (float *) &arrow_new_000030Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000030TexCoords;
		}
		else if (index == 31){
		  temp_struct.NumVerts = &arrow_new_000031NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000031Verts;
		  temp_struct.Normals = (float *) &arrow_new_000031Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000031TexCoords;
		}
		else if (index == 32){
		  temp_struct.NumVerts = &arrow_new_000032NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000032Verts;
		  temp_struct.Normals = (float *) &arrow_new_000032Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000032TexCoords;
		}
		else if (index == 33){
		  temp_struct.NumVerts = &arrow_new_000033NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000033Verts;
		  temp_struct.Normals = (float *) &arrow_new_000033Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000033TexCoords;
		}
		else if (index == 34){
		  temp_struct.NumVerts = &arrow_new_000034NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000034Verts;
		  temp_struct.Normals = (float *) &arrow_new_000034Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000034TexCoords;
		}
		else if (index == 35){
		  temp_struct.NumVerts = &arrow_new_000035NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000035Verts;
		  temp_struct.Normals = (float *) &arrow_new_000035Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000035TexCoords;
		}
		else if (index == 36){
		  temp_struct.NumVerts = &arrow_new_000036NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000036Verts;
		  temp_struct.Normals = (float *) &arrow_new_000036Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000036TexCoords;
		}
		else if (index == 37){
		  temp_struct.NumVerts = &arrow_new_000037NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000037Verts;
		  temp_struct.Normals = (float *) &arrow_new_000037Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000037TexCoords;
		}
		else if (index == 38){
		  temp_struct.NumVerts = &arrow_new_000038NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000038Verts;
		  temp_struct.Normals = (float *) &arrow_new_000038Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000038TexCoords;
		}
		else if (index == 39){
		  temp_struct.NumVerts = &arrow_new_000039NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000039Verts;
		  temp_struct.Normals = (float *) &arrow_new_000039Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000039TexCoords;
		}
		else if (index == 40){
		  temp_struct.NumVerts = &arrow_new_000040NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000040Verts;
		  temp_struct.Normals = (float *) &arrow_new_000040Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000040TexCoords;
		}
		else if (index == 41){
		  temp_struct.NumVerts = &arrow_new_000041NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000041Verts;
		  temp_struct.Normals = (float *) &arrow_new_000041Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000041TexCoords;
		}
		else if (index == 42){
		  temp_struct.NumVerts = &arrow_new_000042NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000042Verts;
		  temp_struct.Normals = (float *) &arrow_new_000042Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000042TexCoords;
		}
		else if (index == 43){
		  temp_struct.NumVerts = &arrow_new_000043NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000043Verts;
		  temp_struct.Normals = (float *) &arrow_new_000043Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000043TexCoords;
		}
		else if (index == 44){
		  temp_struct.NumVerts = &arrow_new_000044NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000044Verts;
		  temp_struct.Normals = (float *) &arrow_new_000044Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000044TexCoords;
		}
		else if (index == 45){
		  temp_struct.NumVerts = &arrow_new_000045NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000045Verts;
		  temp_struct.Normals = (float *) &arrow_new_000045Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000045TexCoords;
		}
		else if (index == 46){
		  temp_struct.NumVerts = &arrow_new_000046NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000046Verts;
		  temp_struct.Normals = (float *) &arrow_new_000046Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000046TexCoords;
		}
		else if (index == 47){
		  temp_struct.NumVerts = &arrow_new_000047NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000047Verts;
		  temp_struct.Normals = (float *) &arrow_new_000047Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000047TexCoords;
		}
		else if (index == 48){
		  temp_struct.NumVerts = &arrow_new_000048NumVerts;
		  temp_struct.Verts = (float *) &arrow_new_000048Verts;
		  temp_struct.Normals = (float *) &arrow_new_000048Normals;
		  temp_struct.TexCoords = (float *) &arrow_new_000048TexCoords;
		}
		*/
	}
	//else if (strcmp (type,"horse") == 1){
	else if (type == 1){
		if (index == 1){
			temp_struct.NumVerts = &cow_000001NumVerts;
			temp_struct.Verts = (float *) &cow_000001Verts;
			temp_struct.Normals = (float *) &cow_000001Normals;
			temp_struct.TexCoords = (float *) &cow_000001TexCoords;
		}
		else if (index == 2){
			temp_struct.NumVerts = &cow_000002NumVerts;
			temp_struct.Verts = (float *) &cow_000002Verts;
			temp_struct.Normals = (float *) &cow_000002Normals;
			temp_struct.TexCoords = (float *) &cow_000002TexCoords;
		}
		else if (index == 3){
			temp_struct.NumVerts = &cow_000003NumVerts;
			temp_struct.Verts = (float *) &cow_000003Verts;
			temp_struct.Normals = (float *) &cow_000003Normals;
			temp_struct.TexCoords = (float *) &cow_000003TexCoords;
		}
		else if (index == 4){
			temp_struct.NumVerts = &cow_000004NumVerts;
			temp_struct.Verts = (float *) &cow_000004Verts;
			temp_struct.Normals = (float *) &cow_000004Normals;
			temp_struct.TexCoords = (float *) &cow_000004TexCoords;
		}
		else if (index == 5){
			temp_struct.NumVerts = &cow_000005NumVerts;
			temp_struct.Verts = (float *) &cow_000005Verts;
			temp_struct.Normals = (float *) &cow_000005Normals;
			temp_struct.TexCoords = (float *) &cow_000005TexCoords;
		}
		else if (index == 6){
			temp_struct.NumVerts = &cow_000006NumVerts;
			temp_struct.Verts = (float *) &cow_000006Verts;
			temp_struct.Normals = (float *) &cow_000006Normals;
			temp_struct.TexCoords = (float *) &cow_000006TexCoords;
		}
		else if (index == 7){
			temp_struct.NumVerts = &cow_000007NumVerts;
			temp_struct.Verts = (float *) &cow_000007Verts;
			temp_struct.Normals = (float *) &cow_000007Normals;
			temp_struct.TexCoords = (float *) &cow_000007TexCoords;
		}
		else if (index == 8){
			temp_struct.NumVerts = &cow_000008NumVerts;
			temp_struct.Verts = (float *) &cow_000008Verts;
			temp_struct.Normals = (float *) &cow_000008Normals;
			temp_struct.TexCoords = (float *) &cow_000008TexCoords;
		}
		else if (index == 9){
			temp_struct.NumVerts = &cow_000009NumVerts;
			temp_struct.Verts = (float *) &cow_000009Verts;
			temp_struct.Normals = (float *) &cow_000009Normals;
			temp_struct.TexCoords = (float *) &cow_000009TexCoords;
		}
		else if (index == 10){
		  temp_struct.NumVerts = &cow_000010NumVerts;
		  temp_struct.Verts = (float *) &cow_000010Verts;
		  temp_struct.Normals = (float *) &cow_000010Normals;
		  temp_struct.TexCoords = (float *) &cow_000010TexCoords;
		}
		else if (index == 11){
		  temp_struct.NumVerts = &cow_000011NumVerts;
		  temp_struct.Verts = (float *) &cow_000011Verts;
		  temp_struct.Normals = (float *) &cow_000011Normals;
		  temp_struct.TexCoords = (float *) &cow_000011TexCoords;
		}
		else if (index == 12){
		  temp_struct.NumVerts = &cow_000012NumVerts;
		  temp_struct.Verts = (float *) &cow_000012Verts;
		  temp_struct.Normals = (float *) &cow_000012Normals;
		  temp_struct.TexCoords = (float *) &cow_000012TexCoords;
		}
		else if (index == 13){
		  temp_struct.NumVerts = &cow_000013NumVerts;
		  temp_struct.Verts = (float *) &cow_000013Verts;
		  temp_struct.Normals = (float *) &cow_000013Normals;
		  temp_struct.TexCoords = (float *) &cow_000013TexCoords;
		}
		else if (index == 14){
		  temp_struct.NumVerts = &cow_000014NumVerts;
		  temp_struct.Verts = (float *) &cow_000014Verts;
		  temp_struct.Normals = (float *) &cow_000014Normals;
		  temp_struct.TexCoords = (float *) &cow_000014TexCoords;
		}
		else if (index == 15){
		  temp_struct.NumVerts = &cow_000015NumVerts;
		  temp_struct.Verts = (float *) &cow_000015Verts;
		  temp_struct.Normals = (float *) &cow_000015Normals;
		  temp_struct.TexCoords = (float *) &cow_000015TexCoords;
		}
		else if (index == 16){
		  temp_struct.NumVerts = &cow_000016NumVerts;
		  temp_struct.Verts = (float *) &cow_000016Verts;
		  temp_struct.Normals = (float *) &cow_000016Normals;
		  temp_struct.TexCoords = (float *) &cow_000016TexCoords;
		}
		else if (index == 17){
		  temp_struct.NumVerts = &cow_000017NumVerts;
		  temp_struct.Verts = (float *) &cow_000017Verts;
		  temp_struct.Normals = (float *) &cow_000017Normals;
		  temp_struct.TexCoords = (float *) &cow_000017TexCoords;
		}
		else if (index == 18){
		  temp_struct.NumVerts = &cow_000018NumVerts;
		  temp_struct.Verts = (float *) &cow_000018Verts;
		  temp_struct.Normals = (float *) &cow_000018Normals;
		  temp_struct.TexCoords = (float *) &cow_000018TexCoords;
		}
		else if (index == 19){
		  temp_struct.NumVerts = &cow_000019NumVerts;
		  temp_struct.Verts = (float *) &cow_000019Verts;
		  temp_struct.Normals = (float *) &cow_000019Normals;
		  temp_struct.TexCoords = (float *) &cow_000019TexCoords;
		}
		else if (index == 20){
		  temp_struct.NumVerts = &cow_000020NumVerts;
		  temp_struct.Verts = (float *) &cow_000020Verts;
		  temp_struct.Normals = (float *) &cow_000020Normals;
		  temp_struct.TexCoords = (float *) &cow_000020TexCoords;
		}
		else if (index == 21){
		  temp_struct.NumVerts = &cow_000021NumVerts;
		  temp_struct.Verts = (float *) &cow_000021Verts;
		  temp_struct.Normals = (float *) &cow_000021Normals;
		  temp_struct.TexCoords = (float *) &cow_000021TexCoords;
		}
		else if (index == 22){
		  temp_struct.NumVerts = &cow_000022NumVerts;
		  temp_struct.Verts = (float *) &cow_000022Verts;
		  temp_struct.Normals = (float *) &cow_000022Normals;
		  temp_struct.TexCoords = (float *) &cow_000022TexCoords;
		}
		else if (index == 23){
		  temp_struct.NumVerts = &cow_000023NumVerts;
		  temp_struct.Verts = (float *) &cow_000023Verts;
		  temp_struct.Normals = (float *) &cow_000023Normals;
		  temp_struct.TexCoords = (float *) &cow_000023TexCoords;
		}
		else if (index == 24){
		  temp_struct.NumVerts = &cow_000024NumVerts;
		  temp_struct.Verts = (float *) &cow_000024Verts;
		  temp_struct.Normals = (float *) &cow_000024Normals;
		  temp_struct.TexCoords = (float *) &cow_000024TexCoords;
		}
		else if (index == 25){
		  temp_struct.NumVerts = &cow_000025NumVerts;
		  temp_struct.Verts = (float *) &cow_000025Verts;
		  temp_struct.Normals = (float *) &cow_000025Normals;
		  temp_struct.TexCoords = (float *) &cow_000025TexCoords;
		}
		else if (index == 26){
		  temp_struct.NumVerts = &cow_000026NumVerts;
		  temp_struct.Verts = (float *) &cow_000026Verts;
		  temp_struct.Normals = (float *) &cow_000026Normals;
		  temp_struct.TexCoords = (float *) &cow_000026TexCoords;
		}
		else if (index == 27){
		  temp_struct.NumVerts = &cow_000027NumVerts;
		  temp_struct.Verts = (float *) &cow_000027Verts;
		  temp_struct.Normals = (float *) &cow_000027Normals;
		  temp_struct.TexCoords = (float *) &cow_000027TexCoords;
		}
		else if (index == 28){
		  temp_struct.NumVerts = &cow_000028NumVerts;
		  temp_struct.Verts = (float *) &cow_000028Verts;
		  temp_struct.Normals = (float *) &cow_000028Normals;
		  temp_struct.TexCoords = (float *) &cow_000028TexCoords;
		}
		else if (index == 29){
		  temp_struct.NumVerts = &cow_000029NumVerts;
		  temp_struct.Verts = (float *) &cow_000029Verts;
		  temp_struct.Normals = (float *) &cow_000029Normals;
		  temp_struct.TexCoords = (float *) &cow_000029TexCoords;
		}
		else if (index == 30){
		  temp_struct.NumVerts = &cow_000030NumVerts;
		  temp_struct.Verts = (float *) &cow_000030Verts;
		  temp_struct.Normals = (float *) &cow_000030Normals;
		  temp_struct.TexCoords = (float *) &cow_000030TexCoords;
		}
		else if (index == 31){
		  temp_struct.NumVerts = &cow_000031NumVerts;
		  temp_struct.Verts = (float *) &cow_000031Verts;
		  temp_struct.Normals = (float *) &cow_000031Normals;
		  temp_struct.TexCoords = (float *) &cow_000031TexCoords;
		}
		else if (index == 32){
		  temp_struct.NumVerts = &cow_000032NumVerts;
		  temp_struct.Verts = (float *) &cow_000032Verts;
		  temp_struct.Normals = (float *) &cow_000032Normals;
		  temp_struct.TexCoords = (float *) &cow_000032TexCoords;
		}
		else if (index == 33){
		  temp_struct.NumVerts = &cow_000033NumVerts;
		  temp_struct.Verts = (float *) &cow_000033Verts;
		  temp_struct.Normals = (float *) &cow_000033Normals;
		  temp_struct.TexCoords = (float *) &cow_000033TexCoords;
		}
		else if (index == 34){
		  temp_struct.NumVerts = &cow_000034NumVerts;
		  temp_struct.Verts = (float *) &cow_000034Verts;
		  temp_struct.Normals = (float *) &cow_000034Normals;
		  temp_struct.TexCoords = (float *) &cow_000034TexCoords;
		}
		else if (index == 35){
		  temp_struct.NumVerts = &cow_000035NumVerts;
		  temp_struct.Verts = (float *) &cow_000035Verts;
		  temp_struct.Normals = (float *) &cow_000035Normals;
		  temp_struct.TexCoords = (float *) &cow_000035TexCoords;
		}
		else if (index == 36){
		  temp_struct.NumVerts = &cow_000036NumVerts;
		  temp_struct.Verts = (float *) &cow_000036Verts;
		  temp_struct.Normals = (float *) &cow_000036Normals;
		  temp_struct.TexCoords = (float *) &cow_000036TexCoords;
		}
		else if (index == 37){
		  temp_struct.NumVerts = &cow_000037NumVerts;
		  temp_struct.Verts = (float *) &cow_000037Verts;
		  temp_struct.Normals = (float *) &cow_000037Normals;
		  temp_struct.TexCoords = (float *) &cow_000037TexCoords;
		}
		else if (index == 38){
		  temp_struct.NumVerts = &cow_000038NumVerts;
		  temp_struct.Verts = (float *) &cow_000038Verts;
		  temp_struct.Normals = (float *) &cow_000038Normals;
		  temp_struct.TexCoords = (float *) &cow_000038TexCoords;
		}
		else if (index == 39){
		  temp_struct.NumVerts = &cow_000039NumVerts;
		  temp_struct.Verts = (float *) &cow_000039Verts;
		  temp_struct.Normals = (float *) &cow_000039Normals;
		  temp_struct.TexCoords = (float *) &cow_000039TexCoords;
		}
		else if (index == 40){
		  temp_struct.NumVerts = &cow_000040NumVerts;
		  temp_struct.Verts = (float *) &cow_000040Verts;
		  temp_struct.Normals = (float *) &cow_000040Normals;
		  temp_struct.TexCoords = (float *) &cow_000040TexCoords;
		}
		else if (index == 41){
		  temp_struct.NumVerts = &cow_000041NumVerts;
		  temp_struct.Verts = (float *) &cow_000041Verts;
		  temp_struct.Normals = (float *) &cow_000041Normals;
		  temp_struct.TexCoords = (float *) &cow_000041TexCoords;
		}
		else if (index == 42){
		  temp_struct.NumVerts = &cow_000042NumVerts;
		  temp_struct.Verts = (float *) &cow_000042Verts;
		  temp_struct.Normals = (float *) &cow_000042Normals;
		  temp_struct.TexCoords = (float *) &cow_000042TexCoords;
		}
		else if (index == 43){
		  temp_struct.NumVerts = &cow_000043NumVerts;
		  temp_struct.Verts = (float *) &cow_000043Verts;
		  temp_struct.Normals = (float *) &cow_000043Normals;
		  temp_struct.TexCoords = (float *) &cow_000043TexCoords;
		}
		else if (index == 44){
		  temp_struct.NumVerts = &cow_000044NumVerts;
		  temp_struct.Verts = (float *) &cow_000044Verts;
		  temp_struct.Normals = (float *) &cow_000044Normals;
		  temp_struct.TexCoords = (float *) &cow_000044TexCoords;
		}
		else if (index == 45){
		  temp_struct.NumVerts = &cow_000045NumVerts;
		  temp_struct.Verts = (float *) &cow_000045Verts;
		  temp_struct.Normals = (float *) &cow_000045Normals;
		  temp_struct.TexCoords = (float *) &cow_000045TexCoords;
		}
		else if (index == 46){
		  temp_struct.NumVerts = &cow_000046NumVerts;
		  temp_struct.Verts = (float *) &cow_000046Verts;
		  temp_struct.Normals = (float *) &cow_000046Normals;
		  temp_struct.TexCoords = (float *) &cow_000046TexCoords;
		}
		else if (index == 47){
		  temp_struct.NumVerts = &cow_000047NumVerts;
		  temp_struct.Verts = (float *) &cow_000047Verts;
		  temp_struct.Normals = (float *) &cow_000047Normals;
		  temp_struct.TexCoords = (float *) &cow_000047TexCoords;
		}
		else if (index == 48){
		  temp_struct.NumVerts = &cow_000048NumVerts;
		  temp_struct.Verts = (float *) &cow_000048Verts;
		  temp_struct.Normals = (float *) &cow_000048Normals;
		  temp_struct.TexCoords = (float *) &cow_000048TexCoords;
		}
		
	}
	else if (type == 2){
		if (index == 1){
			temp_struct.NumVerts = &zombie_000001NumVerts;
			temp_struct.Verts = (float *) &zombie_000001Verts;
			temp_struct.Normals = (float *) &zombie_000001Normals;
			temp_struct.TexCoords = (float *) &zombie_000001TexCoords;
		}
		else if (index == 2){
			temp_struct.NumVerts = &zombie_000002NumVerts;
			temp_struct.Verts = (float *) &zombie_000002Verts;
			temp_struct.Normals = (float *) &zombie_000002Normals;
			temp_struct.TexCoords = (float *) &zombie_000002TexCoords;
		}
		else if (index == 3){
			temp_struct.NumVerts = &zombie_000003NumVerts;
			temp_struct.Verts = (float *) &zombie_000003Verts;
			temp_struct.Normals = (float *) &zombie_000003Normals;
			temp_struct.TexCoords = (float *) &zombie_000003TexCoords;
		}
		else if (index == 4){
			temp_struct.NumVerts = &zombie_000004NumVerts;
			temp_struct.Verts = (float *) &zombie_000004Verts;
			temp_struct.Normals = (float *) &zombie_000004Normals;
			temp_struct.TexCoords = (float *) &zombie_000004TexCoords;
		}
		else if (index == 5){
			temp_struct.NumVerts = &zombie_000005NumVerts;
			temp_struct.Verts = (float *) &zombie_000005Verts;
			temp_struct.Normals = (float *) &zombie_000005Normals;
			temp_struct.TexCoords = (float *) &zombie_000005TexCoords;
		}
		else if (index == 6){
			temp_struct.NumVerts = &zombie_000006NumVerts;
			temp_struct.Verts = (float *) &zombie_000006Verts;
			temp_struct.Normals = (float *) &zombie_000006Normals;
			temp_struct.TexCoords = (float *) &zombie_000006TexCoords;
		}
		else if (index == 7){
			temp_struct.NumVerts = &zombie_000007NumVerts;
			temp_struct.Verts = (float *) &zombie_000007Verts;
			temp_struct.Normals = (float *) &zombie_000007Normals;
			temp_struct.TexCoords = (float *) &zombie_000007TexCoords;
		}
		else if (index == 8){
			temp_struct.NumVerts = &zombie_000008NumVerts;
			temp_struct.Verts = (float *) &zombie_000008Verts;
			temp_struct.Normals = (float *) &zombie_000008Normals;
			temp_struct.TexCoords = (float *) &zombie_000008TexCoords;
		}
		else if (index == 9){
			temp_struct.NumVerts = &zombie_000009NumVerts;
			temp_struct.Verts = (float *) &zombie_000009Verts;
			temp_struct.Normals = (float *) &zombie_000009Normals;
			temp_struct.TexCoords = (float *) &zombie_000009TexCoords;
		}
		else if (index == 10){
		  temp_struct.NumVerts = &zombie_000010NumVerts;
		  temp_struct.Verts = (float *) &zombie_000010Verts;
		  temp_struct.Normals = (float *) &zombie_000010Normals;
		  temp_struct.TexCoords = (float *) &zombie_000010TexCoords;
		}
		else if (index == 11){
		  temp_struct.NumVerts = &zombie_000011NumVerts;
		  temp_struct.Verts = (float *) &zombie_000011Verts;
		  temp_struct.Normals = (float *) &zombie_000011Normals;
		  temp_struct.TexCoords = (float *) &zombie_000011TexCoords;
		}
		else if (index == 12){
		  temp_struct.NumVerts = &zombie_000012NumVerts;
		  temp_struct.Verts = (float *) &zombie_000012Verts;
		  temp_struct.Normals = (float *) &zombie_000012Normals;
		  temp_struct.TexCoords = (float *) &zombie_000012TexCoords;
		}
		else if (index == 13){
		  temp_struct.NumVerts = &zombie_000013NumVerts;
		  temp_struct.Verts = (float *) &zombie_000013Verts;
		  temp_struct.Normals = (float *) &zombie_000013Normals;
		  temp_struct.TexCoords = (float *) &zombie_000013TexCoords;
		}
		else if (index == 14){
		  temp_struct.NumVerts = &zombie_000014NumVerts;
		  temp_struct.Verts = (float *) &zombie_000014Verts;
		  temp_struct.Normals = (float *) &zombie_000014Normals;
		  temp_struct.TexCoords = (float *) &zombie_000014TexCoords;
		}
		else if (index == 15){
		  temp_struct.NumVerts = &zombie_000015NumVerts;
		  temp_struct.Verts = (float *) &zombie_000015Verts;
		  temp_struct.Normals = (float *) &zombie_000015Normals;
		  temp_struct.TexCoords = (float *) &zombie_000015TexCoords;
		}
		else if (index == 16){
		  temp_struct.NumVerts = &zombie_000016NumVerts;
		  temp_struct.Verts = (float *) &zombie_000016Verts;
		  temp_struct.Normals = (float *) &zombie_000016Normals;
		  temp_struct.TexCoords = (float *) &zombie_000016TexCoords;
		}
		else if (index == 17){
		  temp_struct.NumVerts = &zombie_000017NumVerts;
		  temp_struct.Verts = (float *) &zombie_000017Verts;
		  temp_struct.Normals = (float *) &zombie_000017Normals;
		  temp_struct.TexCoords = (float *) &zombie_000017TexCoords;
		}
		else if (index == 18){
		  temp_struct.NumVerts = &zombie_000018NumVerts;
		  temp_struct.Verts = (float *) &zombie_000018Verts;
		  temp_struct.Normals = (float *) &zombie_000018Normals;
		  temp_struct.TexCoords = (float *) &zombie_000018TexCoords;
		}
		else if (index == 19){
		  temp_struct.NumVerts = &zombie_000019NumVerts;
		  temp_struct.Verts = (float *) &zombie_000019Verts;
		  temp_struct.Normals = (float *) &zombie_000019Normals;
		  temp_struct.TexCoords = (float *) &zombie_000019TexCoords;
		}
		else if (index == 20){
		  temp_struct.NumVerts = &zombie_000020NumVerts;
		  temp_struct.Verts = (float *) &zombie_000020Verts;
		  temp_struct.Normals = (float *) &zombie_000020Normals;
		  temp_struct.TexCoords = (float *) &zombie_000020TexCoords;
		}
		else if (index == 21){
		  temp_struct.NumVerts = &zombie_000021NumVerts;
		  temp_struct.Verts = (float *) &zombie_000021Verts;
		  temp_struct.Normals = (float *) &zombie_000021Normals;
		  temp_struct.TexCoords = (float *) &zombie_000021TexCoords;
		}
		else if (index == 22){
		  temp_struct.NumVerts = &zombie_000022NumVerts;
		  temp_struct.Verts = (float *) &zombie_000022Verts;
		  temp_struct.Normals = (float *) &zombie_000022Normals;
		  temp_struct.TexCoords = (float *) &zombie_000022TexCoords;
		}
		else if (index == 23){
		  temp_struct.NumVerts = &zombie_000023NumVerts;
		  temp_struct.Verts = (float *) &zombie_000023Verts;
		  temp_struct.Normals = (float *) &zombie_000023Normals;
		  temp_struct.TexCoords = (float *) &zombie_000023TexCoords;
		}
		else if (index == 24){
		  temp_struct.NumVerts = &zombie_000024NumVerts;
		  temp_struct.Verts = (float *) &zombie_000024Verts;
		  temp_struct.Normals = (float *) &zombie_000024Normals;
		  temp_struct.TexCoords = (float *) &zombie_000024TexCoords;
		}
		else if (index == 25){
		  temp_struct.NumVerts = &zombie_000025NumVerts;
		  temp_struct.Verts = (float *) &zombie_000025Verts;
		  temp_struct.Normals = (float *) &zombie_000025Normals;
		  temp_struct.TexCoords = (float *) &zombie_000025TexCoords;
		}
		else if (index == 26){
		  temp_struct.NumVerts = &zombie_000026NumVerts;
		  temp_struct.Verts = (float *) &zombie_000026Verts;
		  temp_struct.Normals = (float *) &zombie_000026Normals;
		  temp_struct.TexCoords = (float *) &zombie_000026TexCoords;
		}
		else if (index == 27){
		  temp_struct.NumVerts = &zombie_000027NumVerts;
		  temp_struct.Verts = (float *) &zombie_000027Verts;
		  temp_struct.Normals = (float *) &zombie_000027Normals;
		  temp_struct.TexCoords = (float *) &zombie_000027TexCoords;
		}
		else if (index == 28){
		  temp_struct.NumVerts = &zombie_000028NumVerts;
		  temp_struct.Verts = (float *) &zombie_000028Verts;
		  temp_struct.Normals = (float *) &zombie_000028Normals;
		  temp_struct.TexCoords = (float *) &zombie_000028TexCoords;
		}
		else if (index == 29){
		  temp_struct.NumVerts = &zombie_000029NumVerts;
		  temp_struct.Verts = (float *) &zombie_000029Verts;
		  temp_struct.Normals = (float *) &zombie_000029Normals;
		  temp_struct.TexCoords = (float *) &zombie_000029TexCoords;
		}
		else if (index == 30){
		  temp_struct.NumVerts = &zombie_000030NumVerts;
		  temp_struct.Verts = (float *) &zombie_000030Verts;
		  temp_struct.Normals = (float *) &zombie_000030Normals;
		  temp_struct.TexCoords = (float *) &zombie_000030TexCoords;
		}
		else if (index == 31){
		  temp_struct.NumVerts = &zombie_000031NumVerts;
		  temp_struct.Verts = (float *) &zombie_000031Verts;
		  temp_struct.Normals = (float *) &zombie_000031Normals;
		  temp_struct.TexCoords = (float *) &zombie_000031TexCoords;
		}
		else if (index == 32){
		  temp_struct.NumVerts = &zombie_000032NumVerts;
		  temp_struct.Verts = (float *) &zombie_000032Verts;
		  temp_struct.Normals = (float *) &zombie_000032Normals;
		  temp_struct.TexCoords = (float *) &zombie_000032TexCoords;
		}
		else if (index == 33){
		  temp_struct.NumVerts = &zombie_000033NumVerts;
		  temp_struct.Verts = (float *) &zombie_000033Verts;
		  temp_struct.Normals = (float *) &zombie_000033Normals;
		  temp_struct.TexCoords = (float *) &zombie_000033TexCoords;
		}
		else if (index == 34){
		  temp_struct.NumVerts = &zombie_000034NumVerts;
		  temp_struct.Verts = (float *) &zombie_000034Verts;
		  temp_struct.Normals = (float *) &zombie_000034Normals;
		  temp_struct.TexCoords = (float *) &zombie_000034TexCoords;
		}
		else if (index == 35){
		  temp_struct.NumVerts = &zombie_000035NumVerts;
		  temp_struct.Verts = (float *) &zombie_000035Verts;
		  temp_struct.Normals = (float *) &zombie_000035Normals;
		  temp_struct.TexCoords = (float *) &zombie_000035TexCoords;
		}
		else if (index == 36){
		  temp_struct.NumVerts = &zombie_000036NumVerts;
		  temp_struct.Verts = (float *) &zombie_000036Verts;
		  temp_struct.Normals = (float *) &zombie_000036Normals;
		  temp_struct.TexCoords = (float *) &zombie_000036TexCoords;
		}
		else if (index == 37){
		  temp_struct.NumVerts = &zombie_000037NumVerts;
		  temp_struct.Verts = (float *) &zombie_000037Verts;
		  temp_struct.Normals = (float *) &zombie_000037Normals;
		  temp_struct.TexCoords = (float *) &zombie_000037TexCoords;
		}
		else if (index == 38){
		  temp_struct.NumVerts = &zombie_000038NumVerts;
		  temp_struct.Verts = (float *) &zombie_000038Verts;
		  temp_struct.Normals = (float *) &zombie_000038Normals;
		  temp_struct.TexCoords = (float *) &zombie_000038TexCoords;
		}
		else if (index == 39){
		  temp_struct.NumVerts = &zombie_000039NumVerts;
		  temp_struct.Verts = (float *) &zombie_000039Verts;
		  temp_struct.Normals = (float *) &zombie_000039Normals;
		  temp_struct.TexCoords = (float *) &zombie_000039TexCoords;
		}
		else if (index == 40){
		  temp_struct.NumVerts = &zombie_000040NumVerts;
		  temp_struct.Verts = (float *) &zombie_000040Verts;
		  temp_struct.Normals = (float *) &zombie_000040Normals;
		  temp_struct.TexCoords = (float *) &zombie_000040TexCoords;
		}
		else if (index == 41){
		  temp_struct.NumVerts = &zombie_000041NumVerts;
		  temp_struct.Verts = (float *) &zombie_000041Verts;
		  temp_struct.Normals = (float *) &zombie_000041Normals;
		  temp_struct.TexCoords = (float *) &zombie_000041TexCoords;
		}
		else if (index == 42){
		  temp_struct.NumVerts = &zombie_000042NumVerts;
		  temp_struct.Verts = (float *) &zombie_000042Verts;
		  temp_struct.Normals = (float *) &zombie_000042Normals;
		  temp_struct.TexCoords = (float *) &zombie_000042TexCoords;
		}
		else if (index == 43){
		  temp_struct.NumVerts = &zombie_000043NumVerts;
		  temp_struct.Verts = (float *) &zombie_000043Verts;
		  temp_struct.Normals = (float *) &zombie_000043Normals;
		  temp_struct.TexCoords = (float *) &zombie_000043TexCoords;
		}
		else if (index == 44){
		  temp_struct.NumVerts = &zombie_000044NumVerts;
		  temp_struct.Verts = (float *) &zombie_000044Verts;
		  temp_struct.Normals = (float *) &zombie_000044Normals;
		  temp_struct.TexCoords = (float *) &zombie_000044TexCoords;
		}
		else if (index == 45){
		  temp_struct.NumVerts = &zombie_000045NumVerts;
		  temp_struct.Verts = (float *) &zombie_000045Verts;
		  temp_struct.Normals = (float *) &zombie_000045Normals;
		  temp_struct.TexCoords = (float *) &zombie_000045TexCoords;
		}
		else if (index == 46){
		  temp_struct.NumVerts = &zombie_000046NumVerts;
		  temp_struct.Verts = (float *) &zombie_000046Verts;
		  temp_struct.Normals = (float *) &zombie_000046Normals;
		  temp_struct.TexCoords = (float *) &zombie_000046TexCoords;
		}
		else if (index == 47){
		  temp_struct.NumVerts = &zombie_000047NumVerts;
		  temp_struct.Verts = (float *) &zombie_000047Verts;
		  temp_struct.Normals = (float *) &zombie_000047Normals;
		  temp_struct.TexCoords = (float *) &zombie_000047TexCoords;
		}
		else if (index == 48){
		  temp_struct.NumVerts = &zombie_000048NumVerts;
		  temp_struct.Verts = (float *) &zombie_000048Verts;
		  temp_struct.Normals = (float *) &zombie_000048Normals;
		  temp_struct.TexCoords = (float *) &zombie_000048TexCoords;
		}
		
	}
	
	return temp_struct;
} 