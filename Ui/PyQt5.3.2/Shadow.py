from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import sys
from Widget import *

CACHED_SHADOW_RECT_SIZE = (50, 50)


def render_drop_shadow_frame(pixmap, shadow_rect, shadow_color, offset, radius, rect_fill_color):
    pixmap.fill(QColor(0, 0, 0, 0))
    scene = QGraphicsScene()
    rect = QGraphicsRectItem(shadow_rect)
    rect.setBrush(QColor(rect_fill_color))
    rect.setPen(QPen(Qt.NoPen))
    scene.addItem(rect)
    effect = QGraphicsDropShadowEffect(color=shadow_color, blurRadius=radius, offset=offset)
    rect.setGraphicsEffect(effect)
    scene.setSceneRect(QRectF(QPointF(0, 0), QSizeF(pixmap.size())))
    painter = QPainter(pixmap)
    scene.render(painter)
    painter.end()
    scene.clear()
    scene.deleteLater()
    return pixmap


class _DropShadowWidget(QWidget):
    def __init__(self, *args, **kwargs):
        QWidget.__init__(self, *args, **kwargs)
        margin = 20
        QWidget.setContentsMargins(self, margin,margin , margin, margin)
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.offset = QPointF(0, 0)
        self.radius = 20
        self.color = QColor(Qt.black)
        self._shadowPixmap = None
        self._updateShadowPixmap()

    def _updateShadowPixmap(self):
        rect_size = QSize(*CACHED_SHADOW_RECT_SIZE)
        left, top, right, bottom = self.getContentsMargins()
        # Size of the pixmap.
        pixmap_size = QSize(rect_size.width() + left + right,
                            rect_size.height() + top + bottom)
        shadow_rect = QRect(QPoint(left, top), rect_size)
        pixmap = QPixmap(pixmap_size)
        pixmap.fill(QColor(0, 0, 0, 0))
        rect_fill_color = self.palette().color(QPalette.Window)
        pixmap = render_drop_shadow_frame(pixmap, QRectF(shadow_rect),shadow_color=self.color,offset=self.offset,radius=self.radius,rect_fill_color=rect_fill_color)
        self._shadowPixmap = pixmap

    def paintEvent(self, event):
        pixmap = self._shadowPixmap
        widget_rect = QRectF(QPointF(0.0, 0.0), QSizeF(self.size()))
        frame_rect = QRectF(self.contentsRect())
        left, top, right, bottom = self.getContentsMargins()
        pixmap_rect = QRectF(QPointF(0, 0), QSizeF(pixmap.size()))
        # Shadow casting rectangle.
        pixmap_shadow_rect = pixmap_rect.adjusted(left, top, -right, -bottom)
        source_rects = self._shadowPixmapFragments(pixmap_rect, pixmap_shadow_rect)
        target_rects = self._shadowPixmapFragments(widget_rect, frame_rect)
        painter = QPainter(self)
        for source, target in zip(source_rects, target_rects):
            painter.drawPixmap(target, pixmap, source)
        painter.end()

    def _shadowPixmapFragments(self, pixmap_rect, shadow_rect):
        s_left, s_top, s_right, s_bottom = \
            shadow_rect.left(), shadow_rect.top(), \
            shadow_rect.right(), shadow_rect.bottom()
        s_width, s_height = shadow_rect.width(), shadow_rect.height()
        p_width, p_height = pixmap_rect.width(), pixmap_rect.height()

        top_left = QRectF(0.0, 0.0, s_left, s_top)
        top = QRectF(s_left, 0.0, s_width, s_top)
        top_right = QRectF(s_right, 0.0, p_width - s_width, s_top)
        right = QRectF(s_right, s_top, p_width - s_right, s_height)
        right_bottom = QRectF(shadow_rect.bottomRight(), pixmap_rect.bottomRight())
        bottom = QRectF(shadow_rect.bottomLeft(),
                        pixmap_rect.bottomRight() - \
                        QPointF(p_width - s_right, 0.0))
        bottom_left = QRectF(shadow_rect.bottomLeft() - QPointF(s_left, 0.0),
                             pixmap_rect.bottomLeft() + QPointF(s_left, 0.0))
        left = QRectF(pixmap_rect.topLeft() + QPointF(0.0, s_top),
                      shadow_rect.bottomLeft())
        return [top_left, top, top_right, right, right_bottom,
                bottom, bottom_left, left]
