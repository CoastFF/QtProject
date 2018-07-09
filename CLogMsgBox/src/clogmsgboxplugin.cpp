#include "clogmsgbox.h"
#include "clogmsgboxplugin.h"

#include <QtPlugin>

CLogMsgBoxPlugin::CLogMsgBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CLogMsgBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CLogMsgBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CLogMsgBoxPlugin::createWidget(QWidget *parent)
{
    return new CLogMsgBox(parent);
}

QString CLogMsgBoxPlugin::name() const
{
    return QLatin1String("CLogMsgBox");
}

QString CLogMsgBoxPlugin::group() const
{
    return QLatin1String("CoastFF");
}

QIcon CLogMsgBoxPlugin::icon() const
{
    return QIcon(QLatin1String(":/logmsg.ico"));
}

QString CLogMsgBoxPlugin::toolTip() const
{
    return QLatin1String("a CLogMsgBox to show processing msg");
}

QString CLogMsgBoxPlugin::whatsThis() const
{
    return QLatin1String("this is a CustomWidget-CLogMsgBox by CoastFF");
}

bool CLogMsgBoxPlugin::isContainer() const
{
    return false;
}

QString CLogMsgBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CLogMsgBox\" name=\"cLogMsgBox\">\n</widget>\n");
}

QString CLogMsgBoxPlugin::includeFile() const
{
    return QLatin1String("clogmsgbox.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(clogmsgboxplugin, CLogMsgBoxPlugin)
#endif // QT_VERSION < 0x050000
