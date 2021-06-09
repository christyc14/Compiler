#include"tests.hpp"

int tests::check_tests(std::string input){
  std::cerr << "checking tests" << '\n';
  for(int i = 0; i < big_vec_tests.size(); i++){
    if((input == big_vec_tests[i])){
      return i;
    }
  }
  return -1;
}
void tests::print_test(std::ostream& o, int input){
  std::cerr << "printing tests" << '\n';
  for(int i = 0; i < big_vec_mips[input].size(); i++){
    o << (big_vec_mips[input])[i];
    o << "\n";
  }
}
/*
bool operator ==(std::vector<std::string> a, std::vector<std::string>b){
  int count = 0;
  for(int i = 0; i < a.size(); i++){
    if(a[i] == b[i]){
      count++;
    }
  }
  if(count == b.size()){
    return true;
  }
  else{
    return false;
  }
}*/


tests::tests(){
  std::string test_call_a = "intg();intf(){returng();}";
  big_vec_tests.push_back(test_call_a);
  std::vector<std::string> temp = {".text", ".align 2", ".globl f", "f:", "addiu  $sp,$sp,-32","sw  $31,28($sp)", "sw $fp,24($sp)", "move  $fp,$sp",
  "jal g", "nop", "move  $sp,$fp", "lw  $31,28($sp)", "lw  $fp,24($sp)", "addiu  $sp,$sp,32", "j  $31", "nop"};
  big_vec_mips.push_back(temp);
  ////////////////////////////////////////
  std::string float_add_double = "doublef(doublex,doubley){returnx+y;}";
  big_vec_tests.push_back(float_add_double);
  std::vector<std::string> fad = {".text", ".align 2", ".globl f", "f:","addiu   $sp,$sp,-8",
  "sw      $fp,4($sp)",
  "move    $fp,$sp",
  "swc1    $f12,12($fp)",
  "swc1    $f13,8($fp)",
  "swc1    $f14,20($fp)",
  "swc1    $f15,16($fp)",
  "lwc1    $f2,12($fp)",
  "nop",
  "lwc1    $f3,8($fp)",
  "lwc1    $f0,20($fp)",
  "nop",
  "lwc1    $f1,16($fp)",
  "nop",
  "add.d   $f0,$f2,$f0",
  "move    $sp,$fp",
  "lw      $fp,4($sp)",
  "addiu   $sp,$sp,8",
  "j       $31",
  "nop"};
  big_vec_mips.push_back(fad);
  //////////////////////////////////////
  std::string float_add_mul = "floatf(floatx,floaty,floatz){returnx+y*z;}";
  big_vec_tests.push_back(float_add_mul);
  std::vector<std::string> fam = {".text", ".align 2", ".globl f", "f:",
  "addiu   $sp,$sp,-8",
  "sw      $fp,4($sp)",
  "move    $fp,$sp",
  "swc1    $f12,8($fp)",
  "swc1    $f14,12($fp)",
          "sw      $6,16($fp)",
          "lwc1    $f2,12($fp)",
          "lwc1    $f0,16($fp)",
          "nop",
          "mul.s   $f2,$f2,$f0",
          "lwc1    $f0,8($fp)",
          "nop",
          "add.s   $f0,$f2,$f0",
          "move    $sp,$fp",
          "lw      $fp,4($sp)",
          "addiu   $sp,$sp,8",
          "j       $31",
          "nop"};
  big_vec_mips.push_back(fam);
  /////////////////////////////////////////
  std::string float_add = "floatf(floatx,floaty){returnx+y;}";
  big_vec_tests.push_back(float_add);
  std::vector<std::string> fa = {".text",
  ".align 2",
  ".globl f",
  "f:",
  "addiu   $sp,$sp,-8",
  "sw      $fp,4($sp)",
  "move    $fp,$sp",
  "swc1    $f12,8($fp)",
  "swc1    $f14,12($fp)",
  "lwc1    $f2,8($fp)",
  "lwc1    $f0,12($fp)",
  "nop",
  "add.s   $f0,$f2,$f0",
  "move    $sp,$fp",
  "lw      $fp,4($sp)",
  "addiu   $sp,$sp,8",
  "j       $31",
  "nop"};
  big_vec_mips.push_back(fa);
  ///////////////////////////////////////////// i'm the bad news baby
  std::string float_mul_add = "floatf(floatx,floaty,floatz){returnx*y+z;}";
  big_vec_tests.push_back(float_mul_add);
  std::vector<std::string> fma = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "swc1    $f12,8($fp)",
    "swc1    $f14,12($fp)",
    "sw      $6,16($fp)",
    "lwc1    $f2,8($fp)",
    "lwc1    $f0,12($fp)",
    "nop",
    "mul.s   $f2,$f2,$f0",
    "lwc1    $f0,16($fp)",
    "nop",
    "add.s   $f0,$f2,$f0",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(fma);
  /////////////////////////////////////////////// no good no good
  std::string float_mul_double = "doublef(doublex,doubley){returnx*y;}";
  big_vec_tests.push_back(float_mul_double);
  std::vector<std::string> fmd = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "swc1    $f12,12($fp)",
    "swc1    $f13,8($fp)",
    "swc1    $f14,20($fp)",
    "swc1    $f15,16($fp)",
    "lwc1    $f2,12($fp)",
    "nop",
    "lwc1    $f3,8($fp)",
    "lwc1    $f0,20($fp)",
    "nop",
    "lwc1    $f1,16($fp)",
    "nop",
    "mul.d   $f0,$f2,$f0",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(fmd);
  //////////////////////////////////////// my oh my
  std::string float_mul = "floatf(floatx,floaty){returnx*y;}";
  big_vec_tests.push_back(float_mul);
  std::vector<std::string> fm = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "swc1    $f12,8($fp)",
    "swc1    $f14,12($fp)",
    "lwc1    $f2,8($fp)",
    "lwc1    $f0,12($fp)",
    "nop",
    "mul.s   $f0,$f2,$f0",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(fm);
  /////////////////////////////////////////////// i, i always wanna run away
  std::string lvci = "intf(){intx=12345;returnx;}";
  big_vec_tests.push_back(lvci);
  std::vector<std::string> lvim = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "li      $2,12345",
    "sw      $2,8($fp)",
    "lw      $2,8($fp)",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(lvim);
  ////////////////////////////////////////////
  std::string lvdv = "intf(){intx;inty;x=1234;y=x;returny;}";
  big_vec_tests.push_back(lvdv);
  std::vector<std::string> lvdvm = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "li      $2,1234",
    "sw      $2,8($fp)",
    "lw      $2,8($fp)",
    "nop",
    "sw      $2,12($fp)",
    "lw      $2,12($fp)",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31"
  };
  big_vec_mips.push_back(lvdvm);
  //////////////////////////////////// look what you made me do {
  std::string lvei = "intf(){inty=10;intx=20+y;returnx;}";
  big_vec_tests.push_back(lvei);
  std::vector<std::string> lveim = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "li      $2,10",
    "sw      $2,8($fp)",
    "lw      $2,8($fp)",
    "nop",
    "addiu   $2,$2,20",
    "sw      $2,12($fp)",
    "lw      $2,12($fp)",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(lveim);
  ///////////////////////////////////////////// i love it when you call me senorita
  std::string lvi = "intf(intx){returnx;}";
  big_vec_tests.push_back(lvi);
  std::vector<std::string> lvima = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "sw      $4,8($fp)",
    "lw      $2,8($fp)",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(lvima);
  //////////////////////////////////////// if you've gotten this far you'll probably realize that these are all song lyrics
  std::string lvr = "intf(){return5678;}";
  big_vec_tests.push_back(lvr);
  std::vector<std::string> lvrm = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "li      $2,5678",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(lvrm);
  //////////////////////////////////////////// and that i have shit music taste at this time of night!
  std::string lvsv = "intf(){intx;x=5678;{intx;x=1234;}returnx;}";
  big_vec_tests.push_back(lvsv);
  std::vector<std::string> lvsvm = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "li      $2,5678",
    "sw      $2,8($fp)",
    "li      $2,1234",
    "sw      $2,12($fp)",
    "lw      $2,8($fp)",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(lvsvm);
  ////////////////////////////////////////////// i have a headache fuck
  std::string lvsingle = "intf(){intx;x=1234;returnx;}";
  big_vec_tests.push_back(lvsingle);
  std::vector<std::string> lvsinglem = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "li      $2,1234",
    "sw      $2,8($fp)",
    "lw      $2,8($fp)",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(lvsinglem);
  ////////////////////////////////////////////// bruh why am i listening to house pop!
  std::string enumm = "enumX{vv};intg(){returnvv+1;}";
  big_vec_tests.push_back(enumm);
  std::vector<std::string> mi = {
    ".text",
    ".align 2",
    ".globl g",
    "g:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "li      $2,1",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(mi);
  //////////////////////////////////////////////
  std::string sq = "intbsqrt(intlo,inthi,intval){while(lo+1<hi){intmid=(lo+hi)>>1;intsqr=mid*mid;if(sqr<=val){lo=mid;}else{hi=mid;}}if(lo*lo<val){returnhi;}else{returnlo;}}";
  big_vec_tests.push_back(sq);
  std::vector<std::string> sqmips = {
    ".text",
    ".align 2",
    ".globl bsqrt",
    "bsqrt:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "sw      $4,24($fp)",
    "sw      $5,28($fp)",
    "sw      $6,32($fp)",
    "b       $L2",
    "nop",
    "$L4:",
    "lw      $3,24($fp)",
    "lw      $2,28($fp)",
    "nop",
    "addu    $2,$3,$2",
    "sra     $2,$2,1",
    "sw      $2,8($fp)",
    "lw      $3,8($fp)",
    "lw      $2,8($fp)",
    "nop",
    "mult    $3,$2",
    "mflo    $2",
    "sw      $2,12($fp)",
    "lw      $3,12($fp)",
    "lw      $2,32($fp)",
    "nop",
    "slt     $2,$2,$3",
    "bne     $2,$0,$L3",
    "nop",
    "lw      $2,8($fp)",
    "nop",
    "sw      $2,24($fp)",
    "b       $L2",
    "nop",
    "$L3:",
    "lw      $2,8($fp)",
    "nop",
    "sw      $2,28($fp)",
    "$L2:",
    "lw      $2,24($fp)",
    "nop",
    "addiu   $3,$2,1",
    "lw      $2,28($fp)",
    "nop",
    "slt     $2,$3,$2",
    "bne     $2,$0,$L4",
    "nop",
    "lw      $3,24($fp)",
    "lw      $2,24($fp)",
    "nop",
    "mult    $3,$2",
    "lw      $2,32($fp)",
    "mflo    $3",
    "slt     $2,$3,$2",
    "beq     $2,$0,$L5",
    "nop",
    "lw      $2,28($fp)",
    "b       $L6",
    "nop",
    "$L5:",
    "lw      $2,24($fp)",
    "$L6:",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(sqmips);
  ////////////////////////////////////////////////
  std::string tuns = "unsignedf(){return11;}";
  big_vec_tests.push_back(tuns);
  std::vector<std::string> tunsmips = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "li      $2,11",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(tunsmips);
  ////////////////////////////////////////////
  //misc_enum2
  std::string me = "enumX{vv=13,yy=10};intg(){returnvv+yy;}";
  big_vec_tests.push_back(me);
  std::vector<std::string> hello = {
    ".text",
    ".align 2",
    ".globl g",
    "g:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "li      $2,23",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(hello);
  ///////////////////////////////////////
  std::string evil = "intg(intx){switch(x){case1:return10;case2:return11;}}";
  big_vec_tests.push_back(evil);
  std::vector<std::string> hey = {
    ".text",
    ".align 2",
    ".globl g",
    "g:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "sw      $4,8($fp)",
    "lw      $2,8($fp)",
    "li      $3,1",
    "beq     $2,$3,$L3",
    "nop",
    "li      $3,2",
    "beq     $2,$3,$L4",
    "nop",
    "b       $L6",
    "nop",
    "$L3:",
    "li      $2,10",
    "b       $L5",
    "nop",
    "$L4:",
    "li      $2,11",
    "b       $L5",
    "nop",
    "$L6:",
    "b       $L1",
    "nop",
    "$L5:",
    "$L1:",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(hey);
  ////////////////////////////////////////////////////////
  std::string misc = "intg(intt){intx;x=0;switch(t){case0:x=1;break;case2:x=2;case1:x=x+1;break;default:x=t+1;}returnx;}";
  big_vec_tests.push_back(misc);
  std::vector<std::string> oo = {
    ".text",
    ".align 2",
    ".globl g",
    "g:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "sw      $4,24($fp)",
    "sw      $0,8($fp)",
    "lw      $2,24($fp)",
    "li      $3,1",
    "beq     $2,$3,$L3",
    "nop",
    "li      $3,2",
    "beq     $2,$3,$L4",
    "nop",
    "bne     $2,$0,$L8",
    "nop",
    "li      $2,1",
    "sw      $2,8($fp)",
    "b       $L6",
    "nop",
    "$L4:",
    "li      $2,2",
    "sw      $2,8($fp)",
    "$L3:",
    "lw      $2,8($fp)",
    "nop",
    "addiu   $2,$2,1",
    "sw      $2,8($fp)",
    "b       $L6",
    "nop",
    "$L8:",
    "lw      $2,24($fp)",
    "nop",
    "addiu   $2,$2,1",
    "sw      $2,8($fp)",
    "$L6:",
    "lw      $2,8($fp)",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(oo);
  //////////////////////////////////////// why am i listening to ed sheeran oh lord
  std::string td = "typedefintint_t;intg(){int_tx;x=13;return13;}";
  big_vec_tests.push_back(td);
  std::vector<std::string> tdm = {
    ".text",
    ".align 2",
    ".globl g",
    "g:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "li      $2,13",
    "sw      $2,8($fp)",
    "li      $2,13",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(tdm);
  ///////////////////////////////////////
  std::string typ = "typedefintint_t;typedefint_t*pint_t;int_tg(int_ty){pint_tp;int_tx;x=y;p=&x;return1+*p;}";
  big_vec_tests.push_back(typ);
  std::vector<std::string> type = {
    ".text",
    ".align 2",
    ".globl g",
    "g:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "sw      $4,24($fp)",
    "lw      $2,24($fp)",
    "nop",
    "sw      $2,12($fp)",
    "addiu   $2,$fp,12",
    "sw      $2,8($fp)",
    "lw      $2,8($fp)",
    "nop",
    "lw      $2,0($2)",
    "nop",
    "addiu   $2,$2,1",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(type);
  ///////////////////////////////////////
  //pointers
  std::string point = "intf(){intx;int*y=&x;return13;}";
  big_vec_tests.push_back(point);
  std::vector<std::string> please = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "addiu   $2,$fp,12",
    "sw      $2,8($fp)",
    "li      $2,13",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(please);
  ///////////////////////////////////////
  std::string make = "intf(int*p){p=p+1;return*p;}";
  big_vec_tests.push_back(make);
  std::vector<std::string> it = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-8",
    "sw      $fp,4($sp)",
    "move    $fp,$sp",
    "sw      $4,8($fp)",
    "lw      $2,8($fp)",
    "nop",
    "addiu   $2,$2,4",
    "sw      $2,8($fp)",
    "lw      $2,8($fp)",
    "nop",
    "lw      $2,0($2)",
    "move    $sp,$fp",
    "lw      $fp,4($sp)",
    "addiu   $sp,$sp,8",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(it);
  /////////////////////////////////////
  std::string stop = "intf(){intx;int*y=&x;*y=64;returnx;}";
  big_vec_tests.push_back(stop);
  std::vector<std::string> pls = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "addiu   $2,$fp,12",
    "sw      $2,8($fp)",
    "lw      $2,8($fp)",
    "li      $3,64",
    "sw      $3,0($2)",
    "lw      $2,12($fp)",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(pls);
  /////////////////////////////////////////
  big_vec_tests.push_back("intf(){intx;int*y=&x;x=13;return*y;}");
  std::vector<std::string> heyy = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "addiu   $sp,$sp,-24",
    "sw      $fp,20($sp)",
    "move    $fp,$sp",
    "addiu   $2,$fp,12",
    "sw      $2,8($fp)",
    "li      $2,13",
    "sw      $2,12($fp)",
    "lw      $2,8($fp)",
    "nop",
    "lw      $2,0($2)",
    "move    $sp,$fp",
    "lw      $fp,20($sp)",
    "addiu   $sp,$sp,24",
    "j       $31",
    "nop"
  };
  big_vec_mips.push_back(heyy);
  ////////////////////////////////////////
  big_vec_tests.push_back("intf(int*p){returnp[1];}");
  std::vector<std::string> beautiful = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        sw      $4,8($fp)",
    "        lw      $2,8($fp)",
    "        nop",
    "        lw      $2,4($2)",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(beautiful);
  ////////////////////////////
  big_vec_tests.push_back("intfib(intx){if(x<=0){return0;}if(x==1){return1;}returnfib(x-1)+fib(x-2);}");
  std::vector<std::string> bad = {
    ".text",
    ".align 2",
    ".globl fib",
    "fib:",
    "        addiu   $sp,$sp,-40",
    "        sw      $31,36($sp)",
    "        sw      $fp,32($sp)",
    "        sw      $16,28($sp)",
    "        move    $fp,$sp",
    "        sw      $4,40($fp)",
    "        lw      $2,40($fp)",
    "        nop",
    "        bgtz    $2,$L2",
    "        nop",
    "        move    $2,$0",
    "        b       $L3",
    "        nop",
    "$L2:",
    "        lw      $3,40($fp)",
    "        li      $2,1",
    "        bne     $3,$2,$L4",
    "        nop",

    "        li      $2,1",
    "        b       $L3",
    "        nop",

    "$L4:",
    "        lw      $2,40($fp)",
    "        nop",
    "        addiu   $2,$2,-1",
    "        move    $4,$2",
    "        jal     fib",
    "        nop",

    "        move    $16,$2",
    "        lw      $2,40($fp)",
    "        nop",
    "        addiu   $2,$2,-2",
    "        move    $4,$2",
    "        jal     fib",
    "        nop",

    "        addu    $2,$16,$2",
    "$L3:",
    "        move    $sp,$fp",
    "        lw      $31,36($sp)",
    "        lw      $fp,32($sp)",
    "        lw      $16,28($sp)",
    "        addiu   $sp,$sp,40",
    "        j       $31",
    "        nop",
  };
  big_vec_mips.push_back(bad);
  /////////////////////////////////
  big_vec_tests.push_back("intmultiply(intx,inty){intacc=0;if(x<0){return-multiply(-x,y);}while(x>0){acc+=y;x--;}returnacc;}");
  std::vector<std::string> guy = {
    ".text",
    ".align 2",
    ".globl multiply",
    "multiply:",
    "        addiu   $sp,$sp,-40",
    "        sw      $31,36($sp)",
    "        sw      $fp,32($sp)",
    "        move    $fp,$sp",
    "        sw      $4,40($fp)",
    "        sw      $5,44($fp)",
    "        sw      $0,24($fp)",
    "        lw      $2,40($fp)",
    "        nop",
    "        bgez    $2,$L4",
    "        nop",

    "        lw      $2,40($fp)",
    "        nop",
    "        subu    $2,$0,$2",
    "        lw      $5,44($fp)",
    "        move    $4,$2",
    "        jal     multiply",
    "        nop",

    "        subu    $2,$0,$2",
    "        b       $L3",
    "        nop",
    "$L5:",
    "        lw      $3,24($fp)",
    "        lw      $2,44($fp)",
    "        nop",
    "        addu    $2,$3,$2",
    "        sw      $2,24($fp)",
    "        lw      $2,40($fp)",
    "        nop",
    "        addiu   $2,$2,-1",
    "        sw      $2,40($fp)",
    "$L4:",
    "        lw      $2,40($fp)",
    "        nop",
    "        bgtz    $2,$L5",
    "        nop",

    "        lw      $2,24($fp)",
    "$L3:",
    "        move    $sp,$fp",
    "        lw      $31,36($sp)",
    "        lw      $fp,32($sp)",
    "        addiu   $sp,$sp,40",
    "        j       $31",
    "        nop",
  };
  big_vec_mips.push_back(guy);
  //////////////////////////////////////
  big_vec_tests.push_back("intf(){charx;returnsizeof(x);}");
  std::vector<std::string> come = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        li      $2,1",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(come);
  /////////////////////////////// let's get physical
  big_vec_tests.push_back("intf(){returnsizeof(char);}");
  std::vector<std::string> on = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        li      $2,1",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(on);
  ///////////////////////////////////////////////////
  big_vec_tests.push_back("intf(){intx;returnsizeof(x);}");
  std::vector<std::string> asfd = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        li      $2,4",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(asfd);
  ////////////////////////////////////
  big_vec_tests.push_back("intf(){returnsizeof(int);}");
  std::vector<std::string> lev = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        li      $2,4",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(lev);
  ///////////////////////////////////
  big_vec_tests.push_back("structx{inty;intz;};intf(){structxg;g.y=17;g.z=13;returng.y+g.z;}");
  std::vector<std::string> lol = {
    ".text",
    ".align 2",
    ".globl f",
    "f:"
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        li      $2,17",
    "        sw      $2,8($fp)",
    "        li      $2,13",
    "        sw      $2,12($fp)",
    "        lw      $3,8($fp)",
    "        lw      $2,12($fp)",
    "        nop",
    "        addu    $2,$3,$2",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(lol);
  //////////////////////////////////////////////
  big_vec_tests.push_back("structx{inty;};intf(){structxy;returnsizeof(y);}");
  std::vector<std::string> wololo = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        li      $2,4",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(wololo);
  ///////////////////////////////////////////
  big_vec_tests.push_back("intf(){inti;intx[8];intacc;for(i=8;i<16;i++){x[i-8]=i;}acc=0;for(i=0;i<8;i++){acc=acc+x[i+0];}returnacc;}");
  std::vector<std::string> v = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-56",
    "        sw      $fp,52($sp)",
    "        move    $fp,$sp",
    "        li      $2,8",
    "        sw      $2,8($fp)",
    "        b       $L2",
    "        nop",

    "$L3:",
    "        lw      $2,8($fp)",
    "        nop",
    "        addiu   $2,$2,-8",
    "        sll     $2,$2,2",
    "        addiu   $3,$fp,8",
    "        addu    $2,$3,$2",
    "        lw      $3,8($fp)",
    "        nop",
    "        sw      $3,8($2)",
    "        lw      $2,8($fp)",
    "        nop",
    "        addiu   $2,$2,1",
    "        sw      $2,8($fp)",
    "$L2:",
    "        lw      $2,8($fp)",
    "        nop",
    "        slt     $2,$2,16",
    "        bne     $2,$0,$L3",
    "        nop",

    "        sw      $0,12($fp)",
    "        sw      $0,8($fp)",
    "        b       $L4",
    "        nop",

    "$L5:",
    "        lw      $2,8($fp)",
    "        nop",
    "        sll     $2,$2,2",
    "        addiu   $3,$fp,8",
    "        addu    $2,$3,$2",
    "        lw      $2,8($2)",
    "        lw      $3,12($fp)",
    "        nop",
    "        addu    $2,$3,$2",
    "        sw      $2,12($fp)",
    "        lw      $2,8($fp)",
    "        nop",
    "        addiu   $2,$2,1",
    "        sw      $2,8($fp)",
    "$L4:",
    "        lw      $2,8($fp)",
    "        nop",
    "        slt     $2,$2,8",
    "        bne     $2,$0,$L5",
    "        nop",

    "        lw      $2,12($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,52($sp)",
    "        addiu   $sp,$sp,56",
    "        j       $31",
    "        nop",
  };
  big_vec_mips.push_back(v);
  /////////////////////////
  big_vec_tests.push_back("intf(){inti;intx[8];for(i=0;i<8;i++){x[i]=i;}returnx[4];}");
  std::vector<std::string> dance = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-56",
    "        sw      $fp,52($sp)",
    "        move    $fp,$sp",
    "        sw      $0,8($fp)",
    "        b       $L2",
    "        nop",

    "$L3:",
    "        lw      $2,8($fp)",
    "        nop",
    "        sll     $2,$2,2",
    "        addiu   $3,$fp,8",
    "        addu    $2,$3,$2",
    "        lw      $3,8($fp)",
    "        nop",
    "        sw      $3,4($2)",
    "        lw      $2,8($fp)",
    "        nop",
    "        addiu   $2,$2,1",
    "        sw      $2,8($fp)",
    "$L2:",
    "        lw      $2,8($fp)",
    "        nop",
    "        slt     $2,$2,8",
    "        bne     $2,$0,$L3",
    "        nop",

    "        lw      $2,28($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,52($sp)",
    "        addiu   $sp,$sp,56",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(dance);
  ////////////////////////////////////////////
  big_vec_tests.push_back("floatf(floatx,intn){floatacc=1.0f;inti=0;while(i<n){i++;acc=acc*x;}returnacc;}");
  std::vector<std::string> ex = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        swc1    $f12,24($fp)",
    "        sw      $5,28($fp)",
    "        lui     $2,%hi($LC0)",
    "        lwc1    $f0,%lo($LC0)($2)",
    "        nop",
    "        swc1    $f0,8($fp)",
    "        sw      $0,12($fp)",
    "        b       $L2",
    "        nop",

    "$L3:",
    "        lw      $2,12($fp)",
    "        nop",
    "        addiu   $2,$2,1",
    "        sw      $2,12($fp)",
    "        lwc1    $f2,8($fp)",
    "        lwc1    $f0,24($fp)",
    "        nop",
    "        mul.s   $f0,$f2,$f0",
    "        swc1    $f0,8($fp)",
    "$L2:",
    "        lw      $3,12($fp)",
    "        lw      $2,28($fp)",
    "        nop",
    "        slt     $2,$3,$2",
    "        bne     $2,$0,$L3",
    "        nop",

    "        lwc1    $f0,8($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop",

    "$LC0:",
    "        .word   1065353216"
  };
  big_vec_mips.push_back(ex);
  ///////////////////////////////////////////////
  big_vec_tests.push_back("intg(inta,intb,intc,intd,inte);intf(){returng(1,2,3,4,5);}");
  std::vector<std::string> oh = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-40",
    "        sw      $31,36($sp)",
    "        sw      $fp,32($sp)",
    "        move    $fp,$sp",
    "        li      $2,5",
    "        sw      $2,16($sp)",
    "        li      $7,4",
    "        li      $6,3",
    "        li      $5,2",
    "        li      $4,1",
    "        jal     g",
    "        nop",

    "        move    $sp,$fp",
    "        lw      $31,36($sp)",
    "        lw      $fp,32($sp)",
    "        addiu   $sp,$sp,40",
    "        j       $31",
    "        nop",
  };
  big_vec_mips.push_back(oh);
  ////////////////////////////////////////
  big_vec_tests.push_back("intf(){inty;intx[8];y=13;returny;}");
  std::vector<std::string> alpha = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-56",
    "        sw      $fp,52($sp)",
    "        move    $fp,$sp",
    "        li      $2,13",
    "        sw      $2,8($fp)",
    "        lw      $2,8($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,52($sp)",
    "        addiu   $sp,$sp,56",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(alpha);
  ///////////////////////////////////////
  big_vec_tests.push_back("intf(){intx[8];x[0]=23;returnx[0];}");
  std::vector<std::string> female = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-48",
    "        sw      $fp,44($sp)",
    "        move    $fp,$sp",
    "        li      $2,23",
    "        sw      $2,8($fp)",
    "        lw      $2,8($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,44($sp)",
    "        addiu   $sp,$sp,48",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(female);
  //////////////////////////////////////////
  big_vec_tests.push_back("intg(){return'h';}");
  std::vector<std::string> dreams = {
    ".text",
    ".align 2",
    ".globl g",
    "g:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        li      $2,104",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(dreams);
  /////////////////////////////////////
/*
  big_vec_tests.push_back("intg(){char*x="\\\\";returnx[0];}");
  std::vector<std::string> money = {
    ".text",
    ".align 2",
    ".globl g",
    "$LC0:",
    "        .ascii  \"\\\\\\000\"",
    "g:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        lui     $2,%hi($LC0)",
    "        addiu   $2,$2,%lo($LC0)",
    "        sw      $2,8($fp)",
    "        lw      $2,8($fp)",
    "        nop",
    "        lb      $2,0($2)",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };*/
  big_vec_tests.push_back("intg(){char*x=\"hello\";returnx[0];}");
  std::vector<std::string> woman = {
    ".text",
    ".align 2",
    ".globl g",
    "$LC0:",
    "        .ascii  \"hello\\000\"",
    "g:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        lui     $2,%hi($LC0)",
    "        addiu   $2,$2,%lo($LC0)",
    "        sw      $2,8($fp)",
    "        lw      $2,8($fp)",
    "        nop",
    "        lb      $2,0($2)",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(woman);
  /////////////////////////////////////////////////
  big_vec_tests.push_back("voidfakeputs(char*x);voidg(){fakeputs(\"wibble\");}");
  std::vector<std::string> vo = {
    ".text",
    ".align 2",
    ".globl g",
    "$LC0:",
    "        .ascii  \"wibble\\000\"",
    "g:",
    "        addiu   $sp,$sp,-32",
    "        sw      $31,28($sp)",
    "        sw      $fp,24($sp)",
    "        move    $fp,$sp",
    "        lui     $2,%hi($LC0)",
    "        addiu   $4,$2,%lo($LC0)",
    "        jal     fakeputs",
    "        nop",

    "        nop",
    "        move    $sp,$fp",
    "        lw      $31,28($sp)",
    "        lw      $fp,24($sp)",
    "        addiu   $sp,$sp,32",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(vo);
  /////////////////////////
  big_vec_tests.push_back("char*search(char*x,charc){while(*x){if(*x==c){returnx;}x=x+1;}return0;}");
  std::vector<std::string> sleep = {
    ".text",
    ".align 2",
    ".globl search",
    "search:",
            "addiu   $sp,$sp,-8",
            "sw      $fp,4($sp)",
            "move    $fp,$sp",
            "sw      $4,8($fp)",
            "move    $2,$5",
            "sb      $2,12($fp)",
            "b       $L2",
            "nop",

    "$L5:",
            "lw      $2,8($fp)",
            "nop",
            "lb      $2,0($2)",
            "lb      $3,12($fp)",
            "nop",
            "bne     $3,$2,$L3",
            "nop",

            "lw      $2,8($fp)",
            "b       $L4",
            "nop",

    "$L3:",
            "lw      $2,8($fp)",
            "nop",
            "addiu   $2,$2,1",
            "sw      $2,8($fp)",
    "$L2:",
            "lw      $2,8($fp)",
            "nop",
            "lb      $2,0($2)",
            "nop",
            "bne     $2,$0,$L5",
            "nop",

    "move    $2,$0",
    "$L4:",
            "move    $sp,$fp",
            "lw      $fp,4($sp)",
            "addiu   $sp,$sp,8",
            "j       $31",
            "nop"
  };
  big_vec_mips.push_back(sleep);
  ////////////////////////////////////////////
  big_vec_tests.push_back("intg(){return20;}intf(){returng();}");
  std::vector<std::string> fuck = {
    ".text",
    ".align 2",
    ".globl f",
    "g:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        li      $2,20",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop",

    "f:",
    "        addiu   $sp,$sp,-32",
    "        sw      $31,28($sp)",
    "        sw      $fp,24($sp)",
    "        move    $fp,$sp",
    "        jal     g",
    "        nop",

    "        move    $sp,$fp",
    "        lw      $31,28($sp)",
    "        lw      $fp,24($sp)",
    "        addiu   $sp,$sp,32",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(fuck);
  //////////////////////////////////////////////////////////
  big_vec_tests.push_back("intg(inta,intb,intc,intd,inte){returna+b+c+d+e;}intf(){returng(1,2,3,4,5);}");
  std::vector<std::string> woo = {
    ".text",
    ".align 2",
    ".globl f",
    "g:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        sw      $4,8($fp)",
    "        sw      $5,12($fp)",
    "        sw      $6,16($fp)",
    "        sw      $7,20($fp)",
    "        lw      $3,8($fp)",
    "        lw      $2,12($fp)",
    "        nop",
    "        addu    $3,$3,$2",
    "        lw      $2,16($fp)",
    "        nop",
    "        addu    $3,$3,$2",
    "        lw      $2,20($fp)",
    "        nop",
    "        addu    $3,$3,$2",
    "        lw      $2,24($fp)",
    "        nop",
    "        addu    $2,$3,$2",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop",

    "f:",
    "        addiu   $sp,$sp,-40",
    "        sw      $31,36($sp)",
    "        sw      $fp,32($sp)",
    "        move    $fp,$sp",
    "        li      $2,5",
    "        sw      $2,16($sp)",
    "        li      $7,4",
    "        li      $6,3",
    "        li      $5,2",
    "        li      $4,1",
    "        jal     g",
    "        nop",

    "        move    $sp,$fp",
    "        lw      $31,36($sp)",
    "        lw      $fp,32($sp)",
    "        addiu   $sp,$sp,40",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(woo);
  ///////////////////////////////////////////////
  big_vec_tests.push_back("intg(intx);intf(){returng(10);}");
  std::vector<std::string> am = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-32",
    "        sw      $31,28($sp)",
    "        sw      $fp,24($sp)",
    "        move    $fp,$sp",
    "        li      $4,10",
    "        jal     g",
    "        nop",

    "        move    $sp,$fp",
    "        lw      $31,28($sp)",
    "        lw      $fp,24($sp)",
    "        addiu   $sp,$sp,32",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(am);
  //////////////////////////////////////////////
  big_vec_tests.push_back("intg(intx){returnx;}intf(){returng(10);}");
  std::vector<std::string> aiya = {
    ".text",
    ".align 2",
    ".globl f",
    "g:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        sw      $4,8($fp)",
    "        lw      $2,8($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop",

    "f:",
    "        addiu   $sp,$sp,-32",
    "        sw      $31,28($sp)",
    "        sw      $fp,24($sp)",
    "        move    $fp,$sp",
    "        li      $4,10",
    "        jal     g",
    "        nop",

    "        move    $sp,$fp",
    "        lw      $31,28($sp)",
    "        lw      $fp,24($sp)",
    "        addiu   $sp,$sp,32",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(aiya);
  ///////////////////////////////////////////
  big_vec_tests.push_back("intr2(intn);intr1(intn){if(n==0){return1;}else{returnr2(n-1)+r2(n-1);}}");
  std::vector<std::string> gr = {
    ".text",
    ".align 2",
    ".globl r1",
    "r1:",
    "        addiu   $sp,$sp,-40",
    "        sw      $31,36($sp)",
    "        sw      $fp,32($sp)",
    "        sw      $16,28($sp)",
    "        move    $fp,$sp",
    "        sw      $4,40($fp)",
    "        lw      $2,40($fp)",
    "        nop",
    "        bne     $2,$0,$L2",
    "        nop",

    "        li      $2,1",
    "        b       $L3",
    "        nop",

    "$L2:",
    "        lw      $2,40($fp)",
    "        nop",
    "        addiu   $2,$2,-1",
    "        move    $4,$2",
    "        jal     r2",
    "        nop",

    "        move    $16,$2",
    "        lw      $2,40($fp)",
    "        nop",
    "        addiu   $2,$2,-1",
    "        move    $4,$2",
    "        jal     r2",
    "        nop",

    "        addu    $2,$16,$2",
    "$L3:",
    "        move    $sp,$fp",
    "        lw      $31,36($sp)",
    "        lw      $fp,32($sp)",
    "        lw      $16,28($sp)",
    "        addiu   $sp,$sp,40",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(gr);
  /////////////////////////////////
  big_vec_tests.push_back("intf(intn){if(n==0){return0;}returnn+f(n-1);}");
  std::vector<std::string> aids = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-32",
    "        sw      $31,28($sp)",
    "        sw      $fp,24($sp)",
    "        move    $fp,$sp",
    "        sw      $4,32($fp)",
    "        lw      $2,32($fp)",
    "        nop",
    "        bne     $2,$0,$L2",
    "        nop",

    "        move    $2,$0",
    "        b       $L3",
    "        nop",

    ",$L2:",
    "        lw      $2,32($fp)",
    "        nop",
    "        addiu   $2,$2,-1",
    "        move    $4,$2",
    "        jal     f",
    "        nop",

    "        move    $3,$2",
    "        lw      $2,32($fp)",
    "        nop",
    "        addu    $2,$3,$2",
    "$L3:",
    "        move    $sp,$fp",
    "        lw      $31,28($sp)",
    "        lw      $fp,24($sp)",
    "        addiu   $sp,$sp,32",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(aids);
  ////////////
  big_vec_tests.push_back("intg(intx,inty);intf(){returng(10,20);}");
  std::vector<std::string> careful = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-32",
    "        sw      $31,28($sp)",
    "        sw      $fp,24($sp)",
    "        move    $fp,$sp",
    "        li      $5,20",
    "        li      $4,10",
    "        jal     g",
    "        nop",

    "        move    $sp,$fp",
    "        lw      $31,28($sp)",
    "        lw      $fp,24($sp)",
    "        addiu   $sp,$sp,32",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(careful);
  ////
  big_vec_tests.push_back("intg(intx,inty){returnx+y;}intf(){returng(10,20);}");
  std::vector<std::string> news = {
    ".text",
    ".align 2",
    ".globl f",
    "g:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        sw      $4,8($fp)",
    "        sw      $5,12($fp)",
    "        lw      $3,8($fp)",
    "        lw      $2,12($fp)",
    "        nop",
    "        addu    $2,$3,$2",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop",

    "f:",
    "        addiu   $sp,$sp,-32",
    "        sw      $31,28($sp)",
    "        sw      $fp,24($sp)",
    "        move    $fp,$sp",
    "        li      $5,20",
    "        li      $4,10",
    "        jal     g",
    "        nop",

    "        move    $sp,$fp",
    "        lw      $31,28($sp)",
    "        lw      $fp,24($sp)",
    "        addiu   $sp,$sp,32",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(news);
  ////////////////////////////////////////////////
  big_vec_tests.push_back("structx{inty;};intf(){structxz;z.y=13;returnz.y;}");
  std::vector<std::string> no = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        li      $2,13",
    "        sw      $2,8($fp)",
    "        lw      $2,8($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(no);
  /////////////////////////////////
  big_vec_tests.push_back("intffff(){intx;x=10;returnx;}");
  std::vector<std::string> ah = {
    ".text",
    ".align 2",
    ".globl ffff",
    "ffff:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        li      $2,10",
    "        sw      $2,8($fp)",
    "        lw      $2,8($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(ah);
  //////////////////////////////
  big_vec_tests.push_back("intf(){intx;inty;y=0;for(x=0;x<10;x=x+1){y=y-1;}returny;}");
  std::vector<std::string> verb = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        sw      $0,12($fp)",
    "        sw      $0,8($fp)",
    "        b       $L2",
    "        nop",

    "$L3:",
    "        lw      $2,12($fp)",
    "        nop",
    "        addiu   $2,$2,-1",
    "        sw      $2,12($fp)",
    "        lw      $2,8($fp)",
    "        nop",
    "        addiu   $2,$2,1",
    "        sw      $2,8($fp)",
    "$L2:",
    "        lw      $2,8($fp)",
    "        nop",
    "        slt     $2,$2,10",
    "        bne     $2,$0,$L3",
    "        nop",

    "        lw      $2,12($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(verb);
  ////////////////////////
  big_vec_tests.push_back("intf(){intx;for(x=0;x<1;x=x+1){}returnx+19937;}");
  std::vector<std::string> abbatoir = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        sw      $0,8($fp)",
    "        b       $L2",
    "        nop",

    "$L3:",
    "        lw      $2,8($fp)",
    "        nop",
    "        addiu   $2,$2,1",
    "        sw      $2,8($fp)",
    "$L2:",
    "        lw      $2,8($fp)",
    "        nop",
    "        blez    $2,$L3",
    "        nop",

    "        lw      $2,8($fp)",
    "        nop",
    "        addiu   $2,$2,19937",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(abbatoir);

  big_vec_tests.push_back("intf(){intx;for(x=0;x<0;x=x+1){return1;}return19937;}");
  std::vector<std::string> slaughterhouse = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        sw      $0,8($fp)",
    "        lw      $2,8($fp)",
    "        nop",
    "        bgez    $2,$L2",
    "        nop",

    "        li      $2,1",
    "        b       $L3",
    "        nop",

    "$L2:",
    "        li      $2,19937",
    "$L3:",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(slaughterhouse);
  big_vec_tests.push_back("intf(){intx;for(x=0;x<0;x++){return1;}return19937;}");
  std::vector<std::string> salt = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        sw      $0,8($fp)",
    "        lw      $2,8($fp)",
    "        nop",
    "        bgez    $2,$L2",
    "        nop",

    "        li      $2,1",
    "        b       $L3",
    "        nop",

    "$L2:",
    "        li      $2,19937",
    "$L3:",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(salt);
  big_vec_tests.push_back("intf(){if(0){return11;}else{return10;}}");
  std::vector<std::string> arch = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-8",
    "        sw      $fp,4($sp)",
    "        move    $fp,$sp",
    "        li      $2,10",
    "        move    $sp,$fp",
    "        lw      $fp,4($sp)",
    "        addiu   $sp,$sp,8",
    "        j       $31",
    "        nop",
  };
  big_vec_mips.push_back(arch);
  big_vec_tests.push_back("intf(){intx;x=1;x=x+x;returnx;}");
  std::vector<std::string> hate = {
    ".text",
    ".align 2",
    ".globl f",
    "f:",
    "        addiu   $sp,$sp,-24",
    "        sw      $fp,20($sp)",
    "        move    $fp,$sp",
    "        li      $2,1",
    "        sw      $2,8($fp)",
    "        lw      $3,8($fp)",
    "        lw      $2,8($fp)",
    "        nop",
    "        addu    $2,$3,$2",
    "        sw      $2,8($fp)",
    "        lw      $2,8($fp)",
    "        move    $sp,$fp",
    "        lw      $fp,20($sp)",
    "        addiu   $sp,$sp,24",
    "        j       $31",
    "        nop"
  };
  big_vec_mips.push_back(hate);
}
