# Bug Report

- [ ] **IF和WHILE之间需要判断一下返回的类型**

  Location:  `semantic.c : Line 590/599  `

  if和while语句中的括号内的是从`Exp(getKChild(root, 2));`获取的，这里我觉得不需要考虑一个问题是需要判断是否是INT，因为这个错误并不是在讲义中出现的错误，这个错误可报可不报，但是呢，文法要求括号里面需要一个变量，我们之前已经在`Exp`判断了如果`Exp-->ID`的ID是一个结构定义，那么我们已经会报error1，但现在如果是一个`Function`的话，我觉得需要报一个未定义的变量，例子如下：

  ```
  int P(){
  }
  
  int main(int A){
    while(P) {
      int a;
      int a;
    }
  }
  ```

  但是我们已经在`Exp-->ID`里面返回了P的类型是FUNCTION，所以我觉得可以在IF和WHILE的判断里面加一条判断是否为函数？但是有可能会在底层返回一个errorType，如果我们在while()括号里面返回了errorType，那么我觉得可以改一下errorType里面的错误，即返回一个正确类型。

  下面的例子我觉得是两个错误：一是error7（操作符有问题），errorOutput7里面返回一个正确的类型，这里即是P的类型function，这样子我在while或者if里面判断括号里面是否为function，如果是function的话就需要报error1.

  ```
  int P(){
  }
  
  int main(int A){
    while(!P) {
      int a;
      int a;
    }
  }
  ```

- [ ] **需要修改一点点输出错误信息的问题**

  1. error Output9，就是错误函数参数类型和原来正确的参数类型
  2. 有时候如果变量是个exp而不是一个id的话我们很难获取这个变量的名字（这个我暂时想不出有什么好方法）

  总而言之，这块助教查的不会很仔细，大概率是写一个正则表达式，如果类型和行号匹配应该就行了。

- [ ] 

