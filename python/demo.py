# -*- coding: utf-8 -*-
"""
    Python 首次连接STK（此文件只运行一次）
    
    此文件运行后，会在目录[Anaconda3]\Lib\site-packages\comtypes\gen下创建以下模块：
        - AgUiApplicationLib.py
        - AgUiCoreLib.py
        - AgSTKGraphicsLib.py
        - AgSTKVgtLib.py
        - STKObjects.py
        - STKUtil.py
        - AgStkGatorLib
"""
# 导入com相关模块
import comtypes
from comtypes.client import CreateObject

# 打开STK桌面软件，创建STK实例
app = CreateObject("STK11.Application")
# 显示STK GUI界面
app.Visible = True

print('app的类型为：', type(app))

#  获取Object Model的根对象：IAgStkObjectRoot
#  此接口为Object Model中的最顶层接口，由此接口可创建场景、地面站、卫星等
root = app.Personality2

print('root的类型为：', type(root))

#  创建Astrogator相关的模块：AgStkGatorLib
comtypes.client.GetModule(
    (comtypes.GUID("{090D317C-31A7-4AF7-89CD-25FE18F4017C}"), 1, 0))

print('python 首次连接STK完成！')
print('STK Object Model API 的python模块已在', comtypes.__path__[0], '下生成！')

print('请关闭已打开的STK!')
