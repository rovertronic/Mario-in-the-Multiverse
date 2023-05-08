void bhv_cutter_blast_init(void) {
   
}

void bhv_cutter_blast_loop(void) {
   cur_obj_scale_over_time(SCALE_AXIS_X, 20, 1.0f, 10.0f);
   cur_obj_scale_over_time(SCALE_AXIS_Y, 20, 1.0f, 0.1f);
   cur_obj_scale_over_time(SCALE_AXIS_Z, 20, 1.0f, 10.0f);

   if (o->oTimer == 20) {
    obj_mark_for_deletion(o);
   }
}

void bhv_cutter_particle_slash_init(void) {
   
}

void bhv_cutter_particle_slash_loop(void) {

   

   if (o->oBehParams2ndByte == 0) {
      o->oFaceAngleRoll = -0x800;
      o->oMoveAngleRoll = -0x800;
      obj_scale_xyz(o, -1.0f, 1.0f, -1.0f);
   }
   if (o->oBehParams2ndByte == 1) {
      o->oFaceAngleRoll = 0x800;
      o->oMoveAngleRoll = 0x800;
   }
   if (o->oBehParams2ndByte == 2) {
      
      o->oFaceAngleRoll = 0x2000;
      o->oMoveAngleRoll = 0x2000;
      obj_scale_xyz(o, -1.0f, -1.0f, -1.0f);
      
      
   }

   s16 yaw;

   vec3f_get_yaw(&o->oPosVec, gCamera->pos, &yaw);

   o->oFaceAngleYaw = yaw;
   o->oMoveAngleYaw = yaw;

   


   if (o->oTimer == 5) {
      obj_mark_for_deletion(o);
   }
}

