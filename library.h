#include <algorithm>
#define DCACHE_LEN 1024
#define ICACHE_LEN 1024
unsigned int DC_ADDR;
typedef struct  dcache {
  unsigned int addr;
  int use;//num de vezes utilizado
};
typedef struct  icache {
  unsigned int pc;
  int use;//num de vezes utilizado
};
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

enum hazard_t {NO_HAZARD=0, DATA_HAZARD, DATA_HAZARD_NO_FW, CONTROL_HAZARD};

const int N = 127;
branch_pred_t bp_hash[N];
int hazard_count;
int hazard_count_by_type[4];

bool checkBranchPred(bool branch_res, int ac_pc, int npc = 0) {
  bool retval;

  if (bp_hash[(ac_pc / 4) % N].guess() == branch_res &&
      (!branch_res || bp_hash[(ac_pc / 4) % N].jump_pc == npc)) {
    // PURE AWESOMENESS! I BELIEVE IN UNICORNS, RAINBOWS AND CANDY MOUNTAINS
    retval = true;
  } else {
    hazard_count++;
    hazard_count_by_type[CONTROL_HAZARD]++;
    retval = false;
  }

  if(branch_res) bp_hash[(ac_pc / 4) % N].taken(npc);
  else bp_hash[(ac_pc / 4) % N].notTaken();

  return retval;
}
