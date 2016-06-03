CustomWindow BY Qt 
==================
A simple, native and easy to use custom top-level window created by Qt

![CustomWindow](https://raw.githubusercontent.com/IMAN4K/QtPro/master/Resources/Image/CustomWindow BY Qt.gif)

Public Functions
------------------
<table>
    <tr>
      <td></td>
      <td><strong>Window(QWidget *parent = 0)</strong></td>
    </tr>
    <tr>
      <td></td>
      <td><strong>Window(const QString &title, QWidget *parent = 0)</strong></td>
    </tr>
    <tr>
      <td>void</td>
      <td><strong>setIcon(const QPixmap &icon)</strong></td>
    </tr>
    <tr>
      <td>void</td>
      <td><strong>setColor(const QColor &titleColor)</strong></td>
    </tr>
    <tr>
      <td>void</td>
      <td><strong>setRadius(const qreal &radius)</strong></td>
    </tr>
    <tr>
      <td>void</td>
      <td><strong>setBorderWidth(const qint16 &border)</strong></td>
    </tr>
    <tr>
      <td>void</td>
      <td><strong>setCloseDisable(bool disable)</strong></td>
    </tr>
    <tr>
      <td>void</td>
      <td><strong>setMaximizeDisable(bool disable)</strong></td>
    </tr>
    <tr>
      <td>void</td>
      <td><strong>setMinimizeDisable(bool disable)</strong></td>
    </tr>
    <tr>
      <td>qint16</td>
      <td><strong>borderWidth() const</strong></td>
    </tr>
</table>

# Dependencies
* Qt5.5.1

# Build
* Visual Studio® 2013

# Supported OS
* Microsoft Windows® 7 - Windows® 10

# Licensing
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.[[LGPLv3]](https://opensource.org/licenses/lgpl-3.0.html)
