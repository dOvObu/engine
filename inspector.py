import sys
from PyQt5.QtWidgets import QWidget, QApplication, QPushButton
from PyQt5.QtCore import pyqtSlot


class App(QWidget):
  
  def __init__(self):
    super().__init__()
    self.title = 'inspector'
    self.x = 800
    self.y = 150
    self.w = 300
    self.h = 500
    self.components = [10]
    self.initUI()
  
  def initUI(self):
    self.setWindowTitle(self.title)
    self.setGeometry(self.x, self.y, self.w, self.h)
    btn = QPushButton('Add Component', self)
    btn.move(70, 10)
    btn.clicked.connect(self.onClick)
    self.btn = btn
    self.show()
    
  @pyqtSlot()
  def onClick(self):
    self.components.append(10)
    self.btn.move(70, sum(self.components))
    print('component was added')

if __name__=='__main__':
  app = QApplication(sys.argv)
  ex = App()
  sys.exit(app.exec_())
  