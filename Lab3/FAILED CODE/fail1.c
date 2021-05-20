// void optimize_delete();
// InterCode nextInterCode(InterCode code);
// Operand getLeftOperand(InterCode code);
// int isArrayAddress(InterCode code);
// int isLeftOperand(InterCode code);
// int isLeftOperandTemp(InterCode code);
// int isOperandEqual(Operand op1, Operand op2);
// int isCodeEqual(InterCode code1, InterCode code2);
// int isCandidate(InterCode candidate, InterCode code);
// FAILED OPTIMIZE
// void optimize_delete() {
//     InterCode p = head;
//     while(p) 
//     {
//         InterCode nextCode = nextInterCode(p);
//         while(p != nextCode)
//         {
//             if(isLeftOperandTemp(p) || isArrayAddress(p)) 
//             {
//                 p = p->next;
//                 continue;
//             }
//             InterCode q = p->next;
//             while(q != nextCode) 
//             {
//                 if(isCodeEqual(p, q))
//                 {
//                     InterCode tmp = p->next;
//                     while(tmp != q) 
//                     {
//                         if(isLeftOperand(tmp)) {
//                             Operand tmp1 = getLeftOperand(tmp);
//                             if((p->kind == MYADD || p->kind == MYSUB || p->kind == MYMUL || p->kind == MYDIV) && (isOperandEqual(tmp1, p->u.op_binary.op1) || isOperandEqual(tmp1, p->u.op_binary.op2)))
//                                 break;
//                             if(p->kind == MYASSIGN && isOperandEqual(tmp1, p->u.op_assign.right))
//                                 break;
//                         }
//                         tmp = tmp->next;
//                     }
//                     if(tmp != q)
//                         break;
//                     InterCode candidate = q->next;
//                     while(candidate != nextCode) 
//                     {
//                         if(isCandidate(candidate, q))
//                             break;
//                         candidate = candidate->next;
//                     }
//                     InterCode i = q, toDelete = q;
//                     Operand sub = getLeftOperand(p);
//                     Operand sub2 = getLeftOperand(q);
//                     Operand tmp2 = createOperand(sub->kind, sub->u.value);
//                     Operand tmp3 = createOperand(TEMPVAR, sub2->u.value);
//                     while(i != candidate) {
//                         if(i->kind == MYASSIGN) {
//                             if(i->u.op_assign.right->kind != CONSTANT && i->u.op_assign.right->kind != COSNTVAR) {
//                                 if(strcmp(tmp3->u.value, i->u.op_assign.right->u.value) == 0)
//                                     strcpy(i->u.op_assign.right->u.value, tmp2->u.value);
//                                 if(strcmp(tmp3->u.value, i->u.op_assign.left->u.value) == 0)
//                                     strcpy(i->u.op_assign.left->u.value, tmp2->u.value);
//                             }
//                         }
//                         else if(i->kind == MYIFGOTO) {
//                             if(i->u.op_triple.x->kind != CONSTANT && i->u.op_triple.x->kind != COSNTVAR) {
//                                 if(strcmp(tmp3->u.value, i->u.op_triple.x->u.value) == 0)
//                                     strcpy(i->u.op_triple.x->u.value, tmp2->u.value);
//                             }
//                             if(i->u.op_triple.y->kind != CONSTANT && i->u.op_triple.y->kind != COSNTVAR) {
//                                 if(strcmp(tmp3->u.value, i->u.op_triple.y->u.value) == 0)
//                                     strcpy(i->u.op_triple.y->u.value, tmp2->u.value);
//                             }
//                         }
//                         else if(i->kind == MYADD || i->kind == MYSUB || i->kind == MYMUL || i->kind == MYDIV) {
//                             if(i->u.op_binary.op1->kind != CONSTANT && i->u.op_binary.op1->kind != COSNTVAR) {
//                                 if(strcmp(tmp3->u.value, i->u.op_binary.op1->u.value) == 0){
//                                     strcpy(i->u.op_binary.op1->u.value, tmp2->u.value);
//                                 }
//                             }
//                             if(i->u.op_binary.op2->kind != CONSTANT && i->u.op_binary.op2->kind != COSNTVAR) {
//                                 if(strcmp(tmp3->u.value, i->u.op_binary.op2->u.value)==0){
//                                     strcpy(i->u.op_binary.op2->u.value, tmp2->u.value);
//                                 }
//                             }
//                             if(i->u.op_binary.result->kind != CONSTANT && i->u.op_binary.result->kind != COSNTVAR){
//                                 if(strcmp(tmp3->u.value, i->u.op_binary.result->u.value)==0){
//                                     strcpy(i->u.op_binary.result->u.value, tmp2->u.value);
//                                 }
//                             }
//                         }
//                         i = i->next;
//                     }
//                     q = q->next;
//                     deleteCode(toDelete);
//                     continue;
//                 }
//                 q = q->next;
//             }
//             p = p->next;
//         }
//     }
// }

// InterCode nextInterCode(InterCode code) {
//     if(code == NULL || code->next)
//         return NULL;
//     InterCode cur = code->next, pre = code;
//     while(cur) {
//         if(cur->kind == MYLABEL || cur->kind == MYFUNCTION ||pre->kind == MYGOTO || pre->kind == MYIFGOTO)
//             return cur;
//         pre = cur;
//         cur = cur->next;
//     }
//     return NULL;
// }

// Operand getLeftOperand(InterCode code) {
//     Operand res = NULL;
//     switch (code->kind)
//     {
//         case MYASSIGN:
//             res = code->u.op_assign.left;
//             break;
//         case MYADD:
//         case MYSUB:
//         case MYDIV:
//         case MYMUL:
//             res = code->u.op_binary.result;
//             break;
//         default:
//             break;
//     }
//     return res;
// }

// int isArrayAddress(InterCode code) {
//     if(code->kind != MYADD)
//         return 0;
//     if(code->u.op_binary.op1->kind != ADDRESS)
//         return 0;
//     Symbol findTuple = findSymbol(code->u.op_binary.op1->u.value);
//     if(findTuple->type->kind != ARRAY)
//         return 0;
//     return 1;
// }

// int isLeftOperand(InterCode code) {
//     return code->kind == MYASSIGN || code->kind == MYADD || code->kind == MYSUB || code->kind == MYMUL || code->kind == MYDIV;
// }

// int isLeftOperandTemp(InterCode code) {
//     Operand op = getLeftOperand(code);
//     if(op == NULL)
//         return 1;
//     if(op->kind != TEMPVAR)
//         return 1;
//     return 0;
// }

// int isOperandEqual(Operand op1, Operand op2) {
//     if(op1->kind != op2->kind)
//         return 0;
//     if(op1->kind == COSNTVAR || op2->kind == CONSTANT)
//         return op1->u.var_no == op2->u.var_no;
//     else 
//         return !strcmp(op1->u.value, op2->u.value);
// }

// int isCodeEqual(InterCode code1, InterCode code2) {
//     if(code1->kind != code2->kind)
//         return 0;
//     int res = 0;
//     switch (code1->kind)
//     {
//         case MYADD:
//         case MYMUL:
//             res = (isOperandEqual(code1->u.op_binary.op1, code2->u.op_binary.op1) && isOperandEqual(code1->u.op_binary.op2, code2->u.op_binary.op2))
//                || (isOperandEqual(code1->u.op_binary.op1, code2->u.op_binary.op2) && isOperandEqual(code1->u.op_binary.op2, code2->u.op_binary.op1));
//             break;
//         case MYSUB:
//         case MYDIV:
//             res = (isOperandEqual(code1->u.op_binary.op1, code2->u.op_binary.op1) && isOperandEqual(code1->u.op_binary.op2, code2->u.op_binary.op2));
//             break;
//         case MYASSIGN:
//             res = isOperandEqual(code1->u.op_assign.right, code2->u.op_assign.right);
//             break;
//         default:
//             break;
//     }
//     return res;
// }

// int isCandidate(InterCode candidate, InterCode code) {
//     if(candidate->kind != code->kind)
//         return 0;
//     int res = 0;
//     switch (candidate->kind)
//     {
//     case MYASSIGN:
//         res = isOperandEqual(candidate->u.op_assign.left, code->u.op_assign.left);
//         break;
//     case MYADD:
//     case MYSUB:
//     case MYMUL:
//     case MYDIV:
//         res = isOperandEqual(candidate->u.op_binary.result, code->u.op_binary.result);
//         break;
//     default:
//         break;
//     }
//     return res;
// }
