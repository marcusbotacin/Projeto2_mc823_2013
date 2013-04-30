#include <algorithm>

struct control_t {
  int rs, rt, rd;
  bool regwrite, memread;
  int ins_id;

  control_t(int rs=-1, int rt=-1, int rd=-1,
	    bool regwrite=false, bool memread=false):
    rs(rs), rt(rt), rd(rd),
    regwrite(regwrite), memread(memread),
    ins_id(-1) {}
};

struct branch_pred_t {
  // 2-bit branch prediction

  // states:
  //  0,1 = predict taken
  //  2,3 = predict not taken
  int state; // this should be implemented in 2 bits only
  int jump_pc;

branch_pred_t(): state(3), jump_pc(0) {}

  void taken(int jump_pc_) { state = std::max(0, state-1); jump_pc = jump_pc_; }
  void notTaken() { state = std::min(3, state+1); }

  bool guess() {
    if(state == 0 || state == 1) return true;
    else return false;
  }
};

enum hazard_t {NO_HAZARD=0, DATA_HAZARD, CONTROL_HAZARD};
