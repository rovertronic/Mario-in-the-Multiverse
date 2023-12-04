void bhv_cutter_blast_loop(void) {
   cur_obj_scale_over_time(SCALE_AXIS_X, 20, 1.0f, 10.0f);
   cur_obj_scale_over_time(SCALE_AXIS_Y, 20, 1.0f, 0.1f);
   cur_obj_scale_over_time(SCALE_AXIS_Z, 20, 1.0f, 10.0f);

   if (o->oTimer == 20) {
    obj_mark_for_deletion(o);
   }
}
