# gxc-card-game-repo
Migration from https://github.com/EOSIO/eosio-card-game-repo, develop with  vue + gxbjs  + gScatter  



初稿：Li Smith

审阅：

# 第0课 开始之前

# 0.1 课程简介

在这个课程中，我们将要展示构建“元素战争”游戏的每个步骤。

我们会介绍如何使用运行在区块链上面的智能合约，展示如何使用gxbjs 去构建基于JavaScript 的前端，并和gxchain进行通信。

所有的代码可以从GitHub下载，且下载后即可构建一个可运行的版本。



# 0.2 区块链/公信链介绍
## 什么是区块链

区块链是存储交易数据，多中心、分布式存储系统。定期创建一个新的交易区块，并链接到前一个区块。他是分布式的，因为区块链通过许多计算机存储交易。他是多中心的，因为区块链基础设施不属于任何一家公司。区块链能提供信任。加密和共识确保交易是不可变的。区块链提供了弹性和透明度；多中心和分布式意味着区块链的副本能被所有人查看。



## 公信链的好处

公信链具有基于DPoS共识机制的石墨烯底层架构的性能优势，同时具备G-ID、GVM、BaaS、Blockcity pay等链上配套功能，方便各类应用开发。公信链开发了丰富的可信数据组件，逐渐打通数据上链、数据储存、数据计算、数据交换的各个环节，并且已经有了众多落地的应用和实践。



## 先决条件
ubuntu 16.04 （4G+内测  20GB 可用硬盘存储）



## 技术栈
c++开发基础
javascript基础


## 使用的版本
gxsjs 1.3.27
gxc-smart-contract-ide  1.1.0
gscatter 1.1.1

gscatter-js 0.3.4



## 工具版本
gxb-core 1.0.190521



#### **gxb-core内包含工具和程序集**

gxb-core软件提供了一组开发所需的工具和程序：

witness_node   是公信链的节点程序，可以使用插件进行配置，以在单节点和多节点区块链中作为块生成节点或非块生成节点运行。同时也提供REST API服务。



cli_wallet 是公信链的钱包程序，可以存储用户私钥，并用私钥签名交易。同时也提供REST API服务。



可以在以下链接查看如何搭建开发环境，

[https://docs.gxchain.org/zh/advanced/testnet.html#%E4%BB%8B%E7%BB%8D](https://docs.gxchain.org/zh/advanced/testnet.html#介绍)  《如何启动测试网络》

https://docs.gxchain.org/zh/advanced/private_chain.html         《如何搭建私有链》



## 账户和钱包
对区块链执行操作需要进行身份验证，以确保事务的调用者具有执行这些操作的权限。此身份验证通过使用帐户完成。创建帐户时，帐户和帐户公钥将存储在区块链中。创建帐户后，任何由帐户持有人私钥签名的交易都可以通过帐户公钥由区块链进行身份验证。



有关钱包和帐户的更多信息，请访问：

https://docs.gxchain.org/zh/advanced/cli_wallet.html    《 cli_wallet 使用教程》




## 交易

区块链中触发的行为都称之为交易，每个区块中包含了多个交易，交易包含多个operation，operation中包含了调用合约、投票、转账等操作。



https://docs.gxchain.org/zh/advanced/block_operation_object.html  《区块和交易结构介绍》



# 0.3 什么是智能合约

一个公信链的智能合约就是注册在区块链上，且运行在公信节点链程序。智能合约实现了“合约”的语义，操作请求自动存储在区块链中。智能合约定义了接口（操作，参数，数据结构）和实现接口的代码。代码是为WebAssembly编译的，节点可以执行。



从某种意义上说，智能合约是一系列功能（或动作），可以从任何面向UI的用户触发和执行。



可以在此处找到智能合约的介绍

https://docs.gxchain.org/zh/contract/



# 内置类型，api，和actions

#### **智能合约应用程序二进制接口（ABI）**

应用程序二进制接口（ABI）是一种基于JSON的描述，用于在运行时转换JSON和二进制表示之间的用户操作。一旦您通过ABI描述了您的合同，开发人员和用户就可以通过JSON无缝地与您的合同进行交互。

#### 创建智能合约

智能合约源代码可以用WASM（WebAssembly）编译器支持的任何语言编写，公信链目前支持C语言（C / C ++）。

编写代码后，使用gxx实用程序编译智能合约。这是一个为WebAssembly生成代码的工具链。我们使用gxx 和-o标志进行编译，生成`.wasm`文件和-abigen标志，生成`.abi`文件。

```
//编译wast文件，路径需要替换成你自己的
./gxx -o /Users/zhaoxiangfei/code/gxb-core/contracts/examples/helloworld/helloworld.wast /Users/zhaoxiangfei/code/gxb-core/contracts/examples/helloworld/helloworld.cpp

//编译abi文件，路径需要替换成自己的
./gxx -g /Users/zhaoxiangfei/code/gxb-core/contracts/examples/helloworld/helloworld.abi /Users/zhaoxiangfei/code/gxb-core/contracts/examples/helloworld/helloworld.hpp
```



一旦编译了智能合约并生成了ABI，两者都可以通过deploy_contract 上传到区块链：

```
// 部署合约
deploy_contract hello nathan 0 0 /Users/zhaoxiangfei/code/gxb-core/contracts/examples/helloworld GXC true
```



可以在此处找到构建和部署过程的概述：

[https://docs.gxchain.org/zh/contract/#hello-world%E5%90%88%E7%BA%A6%E7%AE%80%E4%BB%8B](https://docs.gxchain.org/zh/contract/#hello-world合约简介)

# abi生成

使用gxx编译智能合约，要求开发人员包含提示，以生成要包含在.abi文件中的代码。提示是C ++ 11样式属性，表示要包含的代码块。

例如，以下//@abi table 属性告诉ABI生成器在ABI中包含表结构：

```
// @abi table users
  struct table_name {
    uint64_t key;
    /*more fields here*/

    auto primary_key() const { return key; }
  };
```



我们还使用另一个宏来确保可以正确调用所有操作。这通常位于智能合约的底部，需要智能合约的名称和操作的名称：

```
GRAPHENE_ABI(nameofclass, （action1）（action2）（action3）)
```



# 调用action

```bash
// 不附带资产
call_contract authorizer_account contract_name  null action_name  "{\"action_parameter\"}" GXC true

// 附带资产(附带资产的action，需要在合约中添加 // @abi payable )
call_contract authorizer_account contract_name  {"amount":10000000,"asset_id":1.3.1} action_name  "{\"action_parameter\"}" GXC true
```

