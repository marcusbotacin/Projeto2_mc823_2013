/******************************************************
 * Processor Module Implementation File.              *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 

#include  "mips1.H"
#include  "mips1_isa.cpp"

#include  "mips1_syscall.H"

//todas as variaveis sao globais
//inicio indica numero da execucao
//hazard_count e o contador de hazards
int inicio=0,hazard_count=0;
//IF e o estagio de Fetch
//IE e o estagio de execucao
//RT e RS sao os registradores origem e destino
int IF_rs,IF_rt,IE_rs,IE_rt;
//instrucoes executadas na rodada passada e nessa
unsigned instr_atual,instr_anterior;

//esta funcao testa se usou memoria na ultima execucao
int useMemory(unsigned instr_anterior)
{
	//considerando load de memoria entre 1 e 7
	if(instr_anterior>=1 && instr_anterior<=7) //intervalo dos loads
	{
	return 1;
	}else{
	return 0;
	}
}
//checa se coincide os registradores
int checkRegister(){

	if(IE_rt==IF_rs || IE_rt==IF_rt) //condicao de hazard
	{
	return 1;
	}else{
	return 0;
	}

}


void mips1::behavior() {

  unsigned ins_id;
  cache_item_t* ins_cache;
  if (has_delayed_load) {
    APP_MEM->load(delayed_load_program);
    ac_pc = ac_start_addr;
    has_delayed_load = false;
  }

  for (;;) {

  bhv_pc = ac_pc;
  if( bhv_pc >= dec_cache_size){
    cerr << "ArchC: Address out of bounds (pc=0x" << hex << bhv_pc << ")." << endl;
    stop();
    return;
  }
  else {
    if( start_up ){
      decode_pc = ac_pc;
      ISA.syscall.set_prog_args(argc, argv);
      start_up=0;
      init_dec_cache();
    }
    else{ 
      decode_pc = bhv_pc;
    }
 
    //!Handling System calls.
    switch( decode_pc ){

#define AC_SYSC(NAME,LOCATION) \
    case LOCATION: \
        ISA.syscall.NAME(); \
      break;  \


#include <ac_syscall.def>

#undef AC_SYSC

    default:

      ins_cache = (DEC_CACHE+decode_pc);
      if ( !ins_cache->valid ){
        quant = 0;
        ins_cache->instr_p = new ac_instr<mips1_parms::AC_DEC_FIELD_NUMBER>((ISA.decoder)->Decode(reinterpret_cast<unsigned char*>(buffer), quant));
        ins_cache->valid = 1;
      }
      instr_vec = ins_cache->instr_p;
      ins_id = instr_vec->get(IDENT);

      if( ins_id == 0 ) {
        cerr << "ArchC Error: Unidentified instruction. " << endl;
        cerr << "PC = " << hex << decode_pc << dec << endl;
        stop();
        return;
      }

      ac_pc = decode_pc;

      ISA.cur_instr_id = ins_id;
      if (!ac_annul_sig) ISA._behavior_instruction(instr_vec->get(1));
      switch (ins_id) {
      case 1: // Instruction lb

	cout<<"chamou lb com "<<instr_vec->get(1)<<" "<<instr_vec->get(2)<<" "<<instr_vec->get(3)<<" "<<instr_vec->get(7)<<"\n";
	IF_rt=instr_vec->get(3);
	IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_lb(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 2: // Instruction lbu
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_lbu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 3: // Instruction lh
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_lh(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 4: // Instruction lhu
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_lhu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 5: // Instruction lw
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
	cout<<"chamou lw com "<<instr_vec->get(1)<<" "<<instr_vec->get(2)<<" "<<instr_vec->get(3)<<" "<<instr_vec->get(7)<<"\n";
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_lw(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 6: // Instruction lwl
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_lwl(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 7: // Instruction lwr
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_lwr(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 8: // Instruction sb
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_sb(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 9: // Instruction sh
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_sh(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 10: // Instruction sw
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_sw(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 11: // Instruction swl
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_swl(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 12: // Instruction swr
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_swr(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 13: // Instruction addi
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_addi(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 14: // Instruction addiu
	//cout<<"global "<<global++;
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
	cout<<"decodificou addiu "<<instr_vec->get(1)<<" "<<instr_vec->get(2)<<" "<<instr_vec->get(3)<<" "<<instr_vec->get(7)<<"\n";
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_addiu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 15: // Instruction slti
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_slti(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 16: // Instruction sltiu
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_sltiu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 17: // Instruction andi
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_andi(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 18: // Instruction ori
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_ori(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 19: // Instruction xori
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_xori(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 20: // Instruction lui
	IF_rt=instr_vec->get(3);
        IF_rs=instr_vec->get(2);
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_lui(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 21: // Instruction add
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_add(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 22: // Instruction addu
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_addu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 23: // Instruction sub
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_sub(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 24: // Instruction subu
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_subu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 25: // Instruction slt
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_slt(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 26: // Instruction sltu
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_sltu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 27: // Instruction instr_and
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_instr_and(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 28: // Instruction instr_or
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_instr_or(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 29: // Instruction instr_xor
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_instr_xor(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 30: // Instruction instr_nor
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_instr_nor(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 31: // Instruction nop
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_nop(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 32: // Instruction sll
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_sll(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 33: // Instruction srl
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_srl(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 34: // Instruction sra
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_sra(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 35: // Instruction sllv
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_sllv(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 36: // Instruction srlv
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_srlv(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 37: // Instruction srav
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_srav(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 38: // Instruction mult
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_mult(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 39: // Instruction multu
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_multu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 40: // Instruction div
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_div(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 41: // Instruction divu
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_divu(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 42: // Instruction mfhi
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_mfhi(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 43: // Instruction mthi
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_mthi(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 44: // Instruction mflo
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_mflo(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 45: // Instruction mtlo
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_mtlo(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 46: // Instruction j
        if (!ac_annul_sig) ISA._behavior_mips1_Type_J(instr_vec->get(1), instr_vec->get(8));
        if (!ac_annul_sig) ISA.behavior_j(instr_vec->get(1), instr_vec->get(8));
        break;
      case 47: // Instruction jal
        if (!ac_annul_sig) ISA._behavior_mips1_Type_J(instr_vec->get(1), instr_vec->get(8));
        if (!ac_annul_sig) ISA.behavior_jal(instr_vec->get(1), instr_vec->get(8));
        break;
      case 48: // Instruction jr
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_jr(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 49: // Instruction jalr
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_jalr(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 50: // Instruction beq
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_beq(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 51: // Instruction bne
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_bne(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 52: // Instruction blez
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_blez(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 53: // Instruction bgtz
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_bgtz(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 54: // Instruction bltz
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_bltz(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 55: // Instruction bgez
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_bgez(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 56: // Instruction bltzal
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_bltzal(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 57: // Instruction bgezal
        if (!ac_annul_sig) ISA._behavior_mips1_Type_I(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        if (!ac_annul_sig) ISA.behavior_bgezal(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(7));
        break;
      case 58: // Instruction sys_call
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_sys_call(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      case 59: // Instruction instr_break
        if (!ac_annul_sig) ISA._behavior_mips1_Type_R(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        if (!ac_annul_sig) ISA.behavior_instr_break(instr_vec->get(1), instr_vec->get(2), instr_vec->get(3), instr_vec->get(4), instr_vec->get(5), instr_vec->get(6));
        break;
      } // switch (ins_id)
      break;
    }

	if(inicio==0) /* primeira execucao, nao vai ter hazard */
	{
	cout<<"primeira execução, sem hazard\n";
	inicio++; //indica que a partir de agora esta valendo
	instr_anterior=ins_id; //ja coloca como anterior
	IE_rt=IF_rt; /* atual vai virar anterior na proxima */
	IE_rs=IF_rs; // igual acima
	}else{

	instr_atual=ins_id; //seta atual para fazer teste
	
	if(useMemory(instr_anterior) && checkRegister()) //hazard se anterior foi memoria e registrador coincide
		{
			cout<<"Hazard\n";
			hazard_count++; //hazard identificado
		}

	cout<<"\n\nInstrucao Atual: "<<instr_atual<<" rs: "<<IF_rs<<" rt: "<<IF_rt<<"\nInstrucao Anterior: "<<instr_anterior<<" rs: "<<IE_rs<<" rt: "<<IE_rt<<"\n\n";


	instr_anterior=instr_atual; //independente de hazard, o que e atual vira anterior
	IE_rt=IF_rt;
	IE_rs=IF_rs;

	}


    if ((!ac_wait_sig) && (!ac_annul_sig)) ac_instr_counter+=1;
    ac_annul_sig = 0;
  }
//!Updating Regs for behavioral simulation.
  if(!ac_wait_sig){
    bhv_pc = ac_pc;
  }
  if (ac_stop_flag) {
    return;
  }
  else {
    if (instr_in_batch < instr_batch_size) {
      instr_in_batch++;
    }
    else {
      instr_in_batch = 0;
      wait(1, SC_NS);
    }
  }

} // for (;;)



} // behavior()

 
#include <ac_sighandlers.H>

void mips1::init() {
  set_args(ac_argc, ac_argv);
#ifdef AC_VERIFY
  set_queue(av[0]);
#endif

  ac_pc = ac_start_addr;
  ISA._behavior_begin();
  cerr << "ArchC: -------------------- Starting Simulation --------------------" << endl;
  InitStat();

  signal(SIGINT, sigint_handler);
  signal(SIGTERM, sigint_handler);
  signal(SIGSEGV, sigsegv_handler);
  signal(SIGUSR1, sigusr1_handler);
#ifdef USE_GDB
  signal(SIGUSR2, sigusr2_handler);
#endif
#ifndef AC_COMPSIM
  set_running();
#else
  void Execute(int argc, char *argv[]);
  Execute(argc, argv);
#endif
}

void mips1::init(int ac, char *av[]) {
  extern char* appfilename;
  ac_init_opt( ac, av);
  ac_init_app( ac, av);
  APP_MEM->load(appfilename);
  set_args(ac_argc, ac_argv);
#ifdef AC_VERIFY
  set_queue(av[0]);
#endif

  ac_pc = ac_start_addr;
  ISA._behavior_begin();
  cerr << "ArchC: -------------------- Starting Simulation --------------------" << endl;
  InitStat();

  signal(SIGINT, sigint_handler);
  signal(SIGTERM, sigint_handler);
  signal(SIGSEGV, sigsegv_handler);
  signal(SIGUSR1, sigusr1_handler);
#ifdef USE_GDB
  signal(SIGUSR2, sigusr2_handler);
#endif
#ifndef AC_COMPSIM
  set_running();
#else
  void Execute(int argc, char *argv[]);
  Execute(argc, argv);
#endif
}

//Stop simulation (may receive exit status)
void mips1::stop(int status) {
  cerr << "ArchC: -------------------- Simulation Finished --------------------" << endl;
  ISA._behavior_end();
  ac_stop_flag = 1;
  ac_exit_status = status;
#ifndef AC_COMPSIM
  set_stopped();
#endif
  cout<<"Hazards: "<<hazard_count<<"\n";
}

void mips1::load(char* program) {
  APP_MEM->load(program);
}

void mips1::delayed_load(char* program) {
  has_delayed_load = true;
  delayed_load_program = new char[strlen(program)];
  strcpy(delayed_load_program, program);
}

// Returns ac_pc value
unsigned mips1::get_ac_pc() {
  return ac_pc;
}

// Assigns value to ac_pc
void mips1::set_ac_pc(unsigned int value) {
  ac_pc = value;
}

// Wrapper function to PrintStat().
void mips1::PrintStat() {
  ac_arch<mips1_parms::ac_word, mips1_parms::ac_Hword>::PrintStat();
}

