# UI Panelable Kit
* 前名: UIProject
* 移植到UE5
* 暂时适配UE4
* 后续版本可能不为UE4做适配

## 当前问题
* Space Widget需要赋值到Panel Controller, 否则初次使用ShowPanel时会崩溃(委托未绑定事件导致)
* 在特殊需求中使用PanelSpace::HidePanel时会触发回调导致隐藏自身Space(比如在PanelSpace::InShowVisibility中使用)

## 迭代需求
* Tick功能的使用(需知UserWidget的Tick触发机制)
* 由于SpaceWidget继承与UIPanel, 理论上可实现父子关系

## 日志
### 23/11/14
* 修复注释

### 23/11/07
* SpaceWidget添加了OnProcessPanel, 可重写达到对RootWidget的适配