# UI Panelable Kit
* 2023/11/05
* 前名: UIProject
* 移植到UE5
* 暂时适配UE4
* 后续版本可能不为UE4做适配

## 当前问题
* Space Widget需要赋值到Panel Controller, 否则初次使用ShowPanel时会崩溃(委托未绑定事件导致)

## 迭代需求
* 可选择PanelSlot类和初始化方式
* Tick功能的使用(需知UserWidget的Tick触发机制)
* 由于SpaceWidget继承与UIPanel, 理论上可实现父子关系
