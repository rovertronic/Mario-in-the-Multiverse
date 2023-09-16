//This is a way of dealing with an issue I mentioned in #mverse-general \
  (search 'TRANSLATION_IS_WEIRD' to find the messages)
#ifndef GE_TRANSLATION_H
#define GE_TRANSLATION_H


#define TRANSLATION_IS_WEIRD

#ifdef TRANSLATION_IS_WEIRD
#define RENDER_GE(mesh_dl, mul)                                     \
	Mtx *mtx = alloc_display_list(sizeof(Mtx));                     \
	mtxf[3][0] *= mul; mtxf[3][1] *= mul; mtxf[3][2] *= mul;        \
	mtxf_to_mtx(mtx, mtxf);                                         \
	gSPMatrix(dlH++, mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);\
	gSPDisplayList(dlH++, mesh_dl);                                 \
	gSPPopMatrix(dlH++, G_MTX_MODELVIEW);                           

#else
#define RENDER_GE(mesh_dl, unused)                                  \
	Mtx *mtx = alloc_display_list(sizeof(Mtx));                     \
	mtxf_to_mtx(mtx, mtxf);                                         \
	gSPMatrix(dlH++, mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);\
	gSPDisplayList(dlH++, mesh_dl);                                 \
	gSPPopMatrix(dlH++, G_MTX_MODELVIEW);                           
#endif


#endif//GE_TRANSLATION_H