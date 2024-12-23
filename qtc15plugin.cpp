#include "qtc15pluginconstants.h"
#include "qtc15plugintr.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>

#include <extensionsystem/iplugin.h>

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>

namespace QtC15Plugin::Internal {

class QtC15PluginPlugin final : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QtC15Plugin.json")

public:
    QtC15PluginPlugin() = default;

    ~QtC15PluginPlugin() final
    {
        // Unregister objects from the plugin manager's object pool
        // Other cleanup, if needed.
    }

    void initialize() final
    {
        // Set up this plugin's factories, if needed.
        // Register objects in the plugin manager's object pool, if needed. (rare)
        // Load settings
        // Add actions to menus
        // Connect to other plugins' signals
        // In the initialize function, a plugin can be sure that the plugins it
        // depends on have passed their initialize() phase.

        // If you need access to command line arguments or to report errors, use the
        //    bool IPlugin::initialize(const QStringList &arguments, QString *errorString)
        // overload.

        auto action = new QAction(Tr::tr("QtC15Plugin Action"), this);
        Core::Command *cmd = Core::ActionManager::registerAction(action,
                                                                 Constants::ACTION_ID,
                                                                 Core::Context(
                                                                     Core::Constants::C_GLOBAL));
        cmd->setDefaultKeySequence(QKeySequence(Tr::tr("Ctrl+Alt+Meta+A")));
        connect(action, &QAction::triggered, this, &QtC15PluginPlugin::triggerAction);

        Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
        menu->menu()->setTitle(Tr::tr("QtC15Plugin"));
        menu->addAction(cmd);
        Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);
    }

    void extensionsInitialized() final
    {
        // Retrieve objects from the plugin manager's object pool, if needed. (rare)
        // In the extensionsInitialized function, a plugin can be sure that all
        // plugins that depend on it have passed their initialize() and
        // extensionsInitialized() phase.
    }

    ShutdownFlag aboutToShutdown() final
    {
        // Save settings
        // Disconnect from signals that are not needed during shutdown
        // Hide UI (if you add UI that is not in the main window directly)
        return SynchronousShutdown;
    }

private:
    void triggerAction()
    {
        QMessageBox::information(Core::ICore::mainWindow(),
                                 Tr::tr("Action Triggered"),
                                 Tr::tr("This is an action from QtC15Plugin."));
    }
};

} // namespace QtC15Plugin::Internal

#include <qtc15plugin.moc>
