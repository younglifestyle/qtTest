#include "widget.h"
#include "ui_widget.h"

void Widget::mousePressEvent(QMouseEvent *e)
{
    if( e->button() == Qt::LeftButton )
    {
        ui->leftButton->setProperty("current", "true");
        ui->leftButton->setStyleSheet("");
    }
    else if( e->button() == Qt::MidButton )
    {
        ui->midButton->setProperty("current", "true");
        ui->midButton->setStyleSheet("");
    }
    else if( e->button() == Qt::RightButton )
    {
        ui->rightButton->setProperty("current", "true");
        ui->rightButton->setStyleSheet("");
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    if( e->button() == Qt::LeftButton )
    {
        ui->leftButton->setProperty("current", "false");
        ui->leftButton->setStyleSheet("");
    }
    else if( e->button() == Qt::MidButton )
    {
        ui->midButton->setProperty("current", "false");
        ui->midButton->setStyleSheet("");
    }
    else if( e->button() == Qt::RightButton )
    {
        ui->rightButton->setProperty("current", "false");
        ui->rightButton->setStyleSheet("");
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    ui->mousePos->setText(QString("move ：(%1, %2)").arg(e->globalX()).arg(e->globalY()));
}

void Widget::keyPressEvent(QKeyEvent *k)
{
    if( (k->modifiers() == Qt::ControlModifier) && (k->key() == Qt::Key_L) )
    {
        *time = time->addSecs(1800);
    }

    switch(k->key())
    {
        case Qt::Key_Escape:ui->EscPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_F1:ui->F1PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F2:ui->F2PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F3:ui->F3PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F4:ui->F4PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F5:ui->F5PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F6:ui->F6PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F7:ui->F7PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F8:ui->F8PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F9:ui->F9PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F10:ui->F10PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F11:ui->F11PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_F12:ui->F12PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break ;
        case Qt::Key_ScrollLock:ui->ScrollLockPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Pause:ui->PauseBreakPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Insert:ui->insertPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Home:ui->homePushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_PageUp:ui->pageUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Delete:ui->deletePushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_End:ui->endPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_PageDown:ui->pageDownPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        //Esc 下面的按键
        case Qt::Key_AsciiTilde:ui->titlePushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_A:ui->aPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_B:ui->bPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_C:ui->cPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_D:ui->dPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_E:ui->ePushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_F:ui->fPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_G:ui->gPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_H:ui->hPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_I:ui->iPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_J:ui->jPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_K:ui->kPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_L:ui->lPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_M:ui->mPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_N:ui->nPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_O:ui->oPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_P:ui->pPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Q:ui->qPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_R:ui->rPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_S:ui->sPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_T:ui->tPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_U:ui->uPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_V:ui->vPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_W:ui->wPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_X:ui->xPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Y:ui->yPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Z:ui->zPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Enter:ui->enterRightPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Return:ui->enterLeftPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_NumLock:ui->NumLockPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        //右边 窗口按键 和右边 Ctrl 之间的按键
        case Qt::Key_Menu:ui->key2PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Comma:ui->commaPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        //分号
        case Qt::Key_Semicolon:ui->semicolonPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Equal:ui->jiaPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Backspace:ui->backPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Question:ui->questionPushButtom->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_At:ui->twoUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_BracketLeft:ui->leftBracketPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_BracketRight:ui->rightBracketPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Backslash:ui->key1PushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_QuoteLeft:ui->titlePushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Underscore:ui->jianPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_AsciiCircum:ui->sixUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Exclam:ui->oneUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_NumberSign:ui->threeUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Dollar:ui->fourUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Percent:ui->fiveUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Ampersand:ui->sevenUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_ParenLeft:ui->nineUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_ParenRight:ui->zeroUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_Apostrophe:ui->colonPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        case Qt::Key_CapsLock:ui->capsLockPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");break;
        /*small key value*/
        case Qt::Key_0:
                if( k->nativeScanCode() == 11 )
                {
                    ui->zeroUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_0 up is press" ;
                }
                else if( k->nativeScanCode() == 82 )
                {
                    ui->zeroRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_0 right is press";
                }
                break;
            case Qt::Key_1:
                if( k->nativeScanCode() == 0x02 )
                {
                    ui->oneUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_1 up is press";
                }
                else if( k->nativeScanCode() == 0x4f )
                {
                    ui->oneRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_1 right is press";
                }
                break;
            case Qt::Key_2:
                if( k->nativeScanCode() == 0x03 )
                {
                    ui->twoUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_2 up is press";
                }
                else if( k->nativeScanCode() == 0x50 )
                {
                    ui->twoRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_2 right is press";
                }
                break;
            case Qt::Key_3:
                if( k->nativeScanCode() == 0x04 )
                {
                    ui->threeUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_3 up is press";
                }
                else if( k->nativeScanCode() == 0x51 )
                {
                    ui->threeRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_3 right is press";
                }
                break;
            case Qt::Key_4:
                if( k->nativeScanCode() == 0x05 )
                {
                    ui->fourUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_4 up is press";
                }
                else if( k->nativeScanCode() == 0x4b )
                {
                    ui->fourRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_4 right is press";
                }
                break;
            case Qt::Key_5:
                if( k->nativeScanCode() == 0x06 )
                {
                    ui->fiveUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_5 up is press";
                }
                else if( k->nativeScanCode() == 0x4c )
                {
                    ui->fiveRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_5 right is press";
                }
                break;
            case Qt::Key_6:
                if( k->nativeScanCode() == 0x07 )
                {
                    ui->sixUpPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");
                    qDebug()<<"key_6 up is press";
                }
                else if( k->nativeScanCode() == 0x4d )
                {
                    ui->sixRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                    qDebug()<<"key_6 right is press";
                }
                break;
        case Qt::Key_7:
            if( k->nativeScanCode() == 0x08 )
            {
                ui->sevenUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_7 up is press";
            }
            else if( k->nativeScanCode() == 0x47 )
            {
                ui->sevenRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_7 right is press";
            }
            break;
        case Qt::Key_8:
            if( k->nativeScanCode() == 0x09 )
            {
                ui->eightUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_8 up is press";
            }
            else if( k->nativeScanCode() == 0x48 )
            {
                ui->eightRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_8 right is press";
            }
            break;
        case Qt::Key_9:
            if( k->nativeScanCode() == 0x0a )
            {
                ui->nineUpPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_9 up is press";
            }
            else if( k->nativeScanCode() == 0x49 )
            {
                ui->nineRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_9 right is press";
            }
            break;
        case Qt::Key_Control:
            if( k->nativeScanCode() == 0x1d )
            {
                ui->ctrlLeftPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_ctrl left is press";
            }
            else if( k->nativeScanCode() == 0x11d )
            {
                ui->ctrlRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_ctrl right is press";
            }
            break;
        case Qt::Key_Shift:
            if( k->nativeScanCode() == 0x2a )
            {
                ui->shiftLeftPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_shift left is press";
            }
            else if( k->nativeScanCode() == 0x36 )
            {
                ui->shiftRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_shift right is press";
            }
            break;
        case Qt::Key_Alt:
            if( k->nativeScanCode() == 0x38 )
            {
                ui->altLeftPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_alt left is press";
            }
            else if( k->nativeScanCode() == 0x138 )
            {
                ui->altRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_alt right is press";
            }
            break;
        case Qt::Key_Meta://windows窗口按键
            if( k->nativeScanCode() == 0x15b )
            {
                ui->windowsLeftPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_windows left is press";
            }
            else if( k->nativeScanCode() == 0x15c )
            {
                ui->windowsRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_windows right is press";
            }
            break;
       case Qt::Key_Period://点
            if( k->nativeScanCode() == 0x34 )
            {
              ui->spotPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_comma left is press";
            }
            if( k->nativeScanCode() == 0x53 )
            {
                ui->delRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_comma right is press";
            }

            break;
        case Qt::Key_Slash://除号
            if( k->nativeScanCode() == 0x35 )
            {
                ui->questionPushButtom->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_slash left is press" ;
            }
            else if(k->nativeScanCode()==0x135)
            {
                ui->rightDivisionPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_slash right is press";
            }
            break;
        case Qt::Key_Minus://small key jianhao
            if( k->nativeScanCode() == 0x4a )
            {
                ui->rightSubPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_jian right is press" ;
            }
            if( k->nativeScanCode() == 0x0c )
            {
                ui->jianPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_jian right is press" ;
            }
            break;
        case Qt::Key_Asterisk://small key chenghao
            if( k->nativeScanCode() == 0x37 )
            {
                ui->rightMulPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_Mul right is press" ;
            }
            break;
        case Qt::Key_Plus://small key jiahao
            if( k->nativeScanCode() == 0x4e )
            {
                ui->jiaRightPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
                qDebug()<<"key_jia right is press" ;
            }
            break;
       default:  break;
    }
//    qDebug("\nnativeScanCode:%x",k->nativeScanCode());
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_AsciiTilde:ui->titlePushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_0: ui->zeroUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->zeroRightPushButton->setStyleSheet("QPushButton{background: transparent;}"); break;
        case Qt::Key_1: ui->oneUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->oneRightPushButton->setStyleSheet("QPushButton{background: transparent;}"); break;
        case Qt::Key_2: ui->twoUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->twoRightPushButton->setStyleSheet("QPushButton{background: transparent;}"); break;
        case Qt::Key_3: ui->threeUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->threeRightPushButton->setStyleSheet("QPushButton{background: transparent;}"); break;
        case Qt::Key_4: ui->fourUpPushButton->setStyleSheet("QPushButton{background: transparent;}"); ui->fourRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_5: ui->fiveUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->fiveRightPushButton->setStyleSheet("QPushButton{background: transparent;}"); break;
        case Qt::Key_6: ui->sixUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->sixRightPushButton->setStyleSheet("QPushButton{background: transparent;}"); break;
        case Qt::Key_7: ui->sevenUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->sevenRightPushButton->setStyleSheet("QPushButton{background: transparent;}"); break;
        case Qt::Key_8: ui->eightUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->eightRightPushButton->setStyleSheet("QPushButton{background: transparent;}"); break;
        case Qt::Key_9: ui->nineUpPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->nineRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_A:ui->aPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_B:ui->bPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_C:ui->cPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_D:ui->dPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_E:ui->ePushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_F:ui->fPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_G:ui->gPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_H:ui->hPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_I:ui->iPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_J:ui->jPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_K:ui->kPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_L:ui->lPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_M:ui->mPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_N:ui->nPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_O:ui->oPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_P:ui->pPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Q:ui->qPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_R:ui->rPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_S:ui->sPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_T:ui->tPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_U:ui->uPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_V:ui->vPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_W:ui->wPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_X:ui->xPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Y:ui->yPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Z:ui->zPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Escape:ui->EscPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_F1:ui->F1PushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_F2:ui->F2PushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_F3:ui->F3PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F4:ui->F4PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F5:ui->F5PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F6:ui->F6PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F7:ui->F7PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F8:ui->F8PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F9:ui->F9PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F10:ui->F10PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F11:ui->F11PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_F12:ui->F12PushButton->setStyleSheet("QPushButton{background: transparent;}");break ;
        case Qt::Key_SysReq:ui->PrintScreenPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_ScrollLock:ui->ScrollLockPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Pause:ui->PauseBreakPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Insert:ui->insertPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Home:ui->homePushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_PageUp:ui->pageUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Delete:ui->deletePushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_End:ui->endPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_PageDown:ui->pageDownPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Enter:ui->enterRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Return:ui->enterLeftPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Shift:ui->shiftLeftPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->shiftRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Alt:ui->altLeftPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->altRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_CapsLock:ui->capsLockPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_NumLock:ui->NumLockPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Control:ui->ctrlLeftPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->ctrlRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Menu:ui->key2PushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Meta:ui->windowsLeftPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->windowsRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Comma:ui->commaPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Minus:ui->rightSubPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->jianPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Plus:ui->jiaRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Period:ui->delRightPushButton->setStyleSheet("QPushButton{background: transparent;}");ui->spotPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Slash:ui->questionPushButtom->setStyleSheet("QPushButton{background: transparent;}");ui->rightDivisionPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Semicolon:ui->semicolonPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Equal:ui->jiaPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Backspace:ui->backPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Backtab:ui->tabPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Question:ui->questionPushButtom->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_At:ui->twoUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_BracketLeft:ui->leftBracketPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_BracketRight:ui->rightBracketPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Backslash:ui->key1PushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Bar:ui->altRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Asterisk:ui->rightMulPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_QuoteLeft:ui->titlePushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Underscore:ui->jianPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_AsciiCircum:ui->sixUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Exclam:ui->oneUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_NumberSign:ui->threeUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Dollar:ui->fourUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Percent:ui->fiveUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Ampersand:ui->sevenUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_ParenLeft:ui->nineUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_ParenRight:ui->zeroUpPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_QuoteDbl:ui->ctrlRightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Apostrophe:ui->colonPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Space:ui->spacePushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Up:ui->upPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Down:ui->downPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Left:ui->leftPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Right:ui->rightPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        case Qt::Key_Tab:ui->tabPushButton->setStyleSheet("QPushButton{background: transparent;}");break;
        default:
            break;
    }
}

bool Widget::event(QEvent *event)
{
    if( event->type() == QEvent::KeyPress )
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);//转化为键盘事件
        if( ke->key() == Qt::Key_Tab ){
            ui->tabPushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
            return true;
        }
    }
    if( event->type() == QEvent::KeyRelease )
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if( ke->key() == Qt::Key_Tab ){
            ui->tabPushButton->setStyleSheet( "QPushButton{background: transparent;}" );
            return true;
        }
    }

    if( event->type() == QEvent::KeyPress )
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Space){
            ui->spacePushButton->setStyleSheet( "background-color:rgb(112, 243, 255)" );
            return true;
        }
    }
    if( event->type() == QEvent::KeyRelease )
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if( ke->key() == Qt::Key_Space ){
            ui->spacePushButton->setStyleSheet( "QPushButton{background: transparent;}" );
            return true;
        }
    }

    if(event->type()==QEvent::KeyPress)
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Up){
            ui->upPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");
            return true;
        }
    }
    if(event->type()==QEvent::KeyRelease)
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Up){
            ui->upPushButton->setStyleSheet("QPushButton{background: transparent;}");
            return true;
        }
    }

    if(event->type()==QEvent::KeyPress)
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Down){
            ui->downPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");
            return true;
        }
    }
    if(event->type()==QEvent::KeyRelease)
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Down){
            ui->downPushButton->setStyleSheet("QPushButton{background: transparent;}");
            return true;
        }
    }

    if(event->type()==QEvent::KeyPress)
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Left){
            ui->leftPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");
            return true;
        }
    }
    if(event->type()==QEvent::KeyRelease)
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Left){
            ui->leftPushButton->setStyleSheet("QPushButton{background: transparent;}");
            return true;
        }
    }

    if(event->type()==QEvent::KeyPress)
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Right){
            ui->rightPushButton->setStyleSheet("background-color:rgb(112, 243, 255)");
            return true;
        }
    }
    if(event->type()==QEvent::KeyRelease)
    {
        QKeyEvent *ke=static_cast<QKeyEvent*>(event);
        if(ke->key()==Qt::Key_Right){
            ui->rightPushButton->setStyleSheet("QPushButton{background: transparent;}");
            return true;
        }
    }
    return QWidget::event(event);
}

