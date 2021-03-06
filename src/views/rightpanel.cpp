/*
 *  Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
 *
 * Author:     daizhengwen <daizhengwen@uniontech.com>
 *
 * Maintainer: daizhengwen <daizhengwen@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "rightpanel.h"
#include"utils.h"
#include"mainwindow.h"

#include <DAnchors>
#include <QPropertyAnimation>

DWIDGET_USE_NAMESPACE

RightPanel::RightPanel(QWidget *parent) : QWidget(parent)
{
    // hide by default.
    QWidget::hide();

    setFixedWidth(240 + 2);

    // Init theme panel.
    // 插件不支持resize,下面代码不需要了
//    DAnchorsBase::setAnchor(this, Qt::AnchorTop, parent, Qt::AnchorTop);
//    DAnchorsBase::setAnchor(this, Qt::AnchorBottom, parent, Qt::AnchorBottom);
//    DAnchorsBase::setAnchor(this, Qt::AnchorRight, parent, Qt::AnchorRight);
}

/*******************************************************************************
 1. @函数:    show
 2. @作者:    ut000610 daizhengwen
 3. @日期:    2020-08-11
 4. @说明:    动画显示
*******************************************************************************/
void RightPanel::show()
{
    QWidget::show();
    QWidget::raise();

    QRect rect = geometry();
    QRect windowRect = window()->geometry();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(250);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    //animation->setStartValue(QRect(windowRect.width(), rect.y(), rect.width(), windowRect.height() - 50));
    //animation->setEndValue(QRect(windowRect.width() - rect.width(), rect.y(), rect.width(), windowRect.height() - 50));
    if (window()->isFullScreen()) {
        animation->setStartValue(QRect(windowRect.width(), rect.y(), rect.width(), windowRect.height()));
        animation->setEndValue(QRect(windowRect.width() - rect.width(), rect.y(), rect.width(), windowRect.height()));
    } else {
        animation->setStartValue(QRect(windowRect.width(), rect.y(), rect.width(), windowRect.height() - 50));
        animation->setEndValue(QRect(windowRect.width() - rect.width(), rect.y(), rect.width(), windowRect.height() - 50));
    }
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    //    connect(animation, &QPropertyAnimation::valueChanged, this, [=] { m_themeView->adjustScrollbarMargins(); });
}

/*******************************************************************************
 1. @函数:    hideAnim
 2. @作者:    ut000610 daizhengwen
 3. @日期:    2020-08-11
 4. @说明:    动画隐藏
*******************************************************************************/
void RightPanel::hideAnim()
{
    // 隐藏状态不处理
    if (!isVisible()) {
        return;
    }
    QRect rect = geometry();
    QRect windowRect = window()->geometry();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(250);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    //animation->setStartValue(
    //    QRect(windowRect.width() - rect.width(), rect.y(), rect.width(), windowRect.height() - 50));
    //animation->setEndValue(QRect(windowRect.width(), rect.y(), rect.width(), windowRect.height() - 50));
    if (window()->isFullScreen()) {
        animation->setStartValue(QRect(windowRect.width() - rect.width(), rect.y(), rect.width(), windowRect.height()));
        animation->setEndValue(QRect(windowRect.width(), rect.y(), rect.width(), windowRect.height()));
    } else {
        animation->setStartValue(QRect(windowRect.width() - rect.width(), rect.y(), rect.width(), windowRect.height() - 50));
        animation->setEndValue(QRect(windowRect.width(), rect.y(), rect.width(), windowRect.height() - 50));
    }


    animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animation, &QPropertyAnimation::finished, this, &QWidget::hide);
}

/*******************************************************************************
 1. @函数:    hideEvent
 2. @作者:    ut001121 张猛
 3. @日期:    2020-08-01
 4. @说明:    处理隐藏事件
*******************************************************************************/
void RightPanel::hideEvent(QHideEvent *event)
{
    /***add begin by ut001121 zhangmeng 20200801 解决终端插件被隐藏时焦点回退到工作区的问题***/
    if(QApplication::focusWidget())
    {
        // 焦点控件的全局坐标
        QPoint focusPoint = QApplication::focusWidget()->mapToGlobal(QPoint(0,0));
        // 焦点相对当前控件坐标
        focusPoint = mapFromGlobal(focusPoint);

        // 判断是否包含坐标
        if(rect().contains(focusPoint)){
            Utils::getMainWindow(this)->focusCurrentPage();
        }
    }
    /***add end by ut001121***/

    QWidget::hideEvent(event);
}
