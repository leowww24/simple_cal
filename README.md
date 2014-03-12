simple_cal
==========

基于文法分析的计算器程序原型

文法规则：
Expression:
  Term
  Expression "+" Term
  Expression "-" Term
Term:
  Primary
  Term "*" Primary
  Term "/" Primary
  Term "%" Primary
Primary
  Number
  "(" Expression ")"
Number:
  floating-point-literal
