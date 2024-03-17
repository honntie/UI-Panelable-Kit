# UI Panelable Kit
* 前名: UIProject
* 移植到UE5
* 暂时适配UE4
* 后续版本可能不为UE4做适配

## 迭代需求
* Tick功能的使用(需知UserWidget的Tick触发机制)
* 在PanelController上建立UI Layer

## 日志
### 24/03/17
* 分支更新，重置大部分函数，大量改名
* UIPanel
    * SetDisplay改名SetShow
    * OnShow和OnHide新增变量ESlateVisibility&（可改）
    * OnShow和OnHide蓝图和C++版本重载函数区分
    * 移除OnLogouted和OnRegistered

* PanelSpace
    * 新增User表示使用自身的PanelController，并且可根据DefaultUser自动生成。如果已被赋值，则无法使用（可赋值空）
    * 移除默认显示/隐藏自身的ESlateVisibility，新增OnEnable和OnDisable函数代替初次显示和所有面板隐藏事件
    * 虚函数改名，[介词][动词][名词]转成[介词][名词][动词]（例如OnShowPanel -> OnPanelShow）

* PanelController
    * 基类Component改为PrimaryDataAsset
    * 移除动态多播委托
    * SetPanelSpace如果已被赋值，则无法使用（可赋值空）
    * 新增Init和Reset函数对应初始化和释放
    * 新增InitPushPanels: TSet<TSubclassOf<UUIPanelWidget>>变量，为Init函数使用

### 23/11/14
* 修复注释

### 23/11/07
* SpaceWidget添加了OnProcessPanel, 可重写达到对RootWidget的适配