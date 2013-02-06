/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

/**
 * @file plugin.cpp
 * @author Wintermute Development <wntr-devel@thesii.org>
 *
 */

#include <QFile>
#include <QDebug>

#include "core.hpp"
#include "factory.hpp"
#include "shellplugin.hpp"
#include "pluginprivate.hpp"
#include "plugin.hpp"

WINTER_USE_NAMESPACE

AbstractPluginPrivate::AbstractPluginPrivate (AbstractPlugin* p_qPtr) :
    pluginLoader (0), q_ptr (p_qPtr), settings (0), configuration (0)
{

}

void AbstractPluginPrivate::doStart()
{
    Q_Q (AbstractPlugin);
    q->start();
    emit q->started();
}

void AbstractPluginPrivate::doStop()
{
    Q_Q (AbstractPlugin);
    q->stop();
    emit q->stopped();
}

bool AbstractPluginPrivate::loadPackages() const
{
    Q_Q (const AbstractPlugin);
    const QStringList deps = q->packages();
    //qDebug () << "(core) [AbstractPlugin] Loading packages for" << q->name () << ";" << deps.length () << "package(s) to be loaded.";
    foreach (const QString dep, deps) {
        const QString depName = dep.split (" ").at (0);
    }

    return true;
}

bool AbstractPluginPrivate::loadPlugins() const
{
    Q_Q (const AbstractPlugin);
    const QStringList plgnLst = q->plugins();
    qDebug () << "(core) [AbstractPluginPrivate::loadPlugins()] Loading plug-ins for"
              << q->name () << ";"
              << plgnLst.length () << "plug-in(s) to be loaded.";

    foreach (const QString plgnDepStr, plgnLst) {
        QString plgnUuid;
        ShellPlugin* gnrc = 0;

        if (plgnDepStr.contains (" ")) {
            // @todo: Add plug-in version resolution code.
        }
        else {
            plgnUuid = plgnDepStr;
        }

        gnrc = new ShellPlugin (plgnUuid);
        qDebug() << plgnUuid;

        if (Factory::loadedPlugins().contains (plgnUuid))
            qDebug () << "(core) [AbstractPluginPrivate::loadPlugins()] Dependency"
                      << gnrc->name()
                      << "already loaded.";
        else {
            qDebug() << "(core) [AbstractPluginPrivate::loadPlugins()] Loading dependency"
                     << gnrc->name() << "...";

            if (gnrc->loadLibrary()) {
                qWarning() << "(core) [AbstractPluginPrivate::loadPlugins()] Loaded symbols of plug-in"
                           << Factory::attribute (plgnUuid, "Description/Name").toString() << ".";
            }
            else {
                qWarning() << "(core) [AbstractPluginPrivate::loadPlugins] Unable to load symbols of dependency"
                           << gnrc->name() << ":" << gnrc->d_func()->pluginLoader->errorString();

                return false;
            }
        }
    }
    qDebug() << "(core) [AbstractPluginPrivate::loadPlugins()] Dependent plug-ins loaded.";
    return true;
}

void AbstractPluginPrivate::loadSettings (const QString& p_uuid)
{
    settings = Factory::getPluginSettings (p_uuid);
    configuration = new QSettings ("Synthetic Intellect Institute", p_uuid);
}

AbstractPluginPrivate::~AbstractPluginPrivate()
{

}

AbstractPlugin::AbstractPlugin() : QObject(),
    d_ptr (new AbstractPluginPrivate (this))
{
}

AbstractPlugin::AbstractPlugin (QPluginLoader* p_pluginLoader) :
    QObject (p_pluginLoader), d_ptr (new AbstractPluginPrivate (this))
{
    Q_D (AbstractPlugin);
    d->pluginLoader = p_pluginLoader;
}

AbstractPlugin::AbstractPlugin (const AbstractPlugin& p_other) : QObject (p_other.parent()),
    d_ptr (const_cast<AbstractPluginPrivate*> (p_other.d_ptr.data()))
{
    Q_D (AbstractPlugin);
    d->q_ptr = this;
}

QString AbstractPlugin::author() const
{
    Q_D (const AbstractPlugin);
    return d->settings->value ("Description/Author").toString();
}

QString AbstractPlugin::name() const
{
    Q_D (const AbstractPlugin);

    if (d->settings->contains ("Description/Name")) {
        return d->settings->value ("Description/Name").toString();
    }

    return QString::null;
}

QString AbstractPlugin::vendorName() const
{
    Q_D (const AbstractPlugin);
    return d->settings->value ("Description/Vendor").toString();
}

QString AbstractPlugin::uuid() const
{
    Q_D (const AbstractPlugin);
    return d->settings->value ("Version/UUID").toString();
}

QString AbstractPlugin::description() const
{
    Q_D (const AbstractPlugin);
    return d->settings->value ("Description/Blurb").toString();
}

QString AbstractPlugin::webPage() const
{
    Q_D (const AbstractPlugin);
    return d->settings->value ("Description/WebPage").toString();
}

double AbstractPlugin::version() const
{
    Q_D (const AbstractPlugin);
    return d->settings->value ("Version/Plugin").toDouble();
}

double AbstractPlugin::compatVersion() const
{
    Q_D (const AbstractPlugin);
    return d->settings->value ("Version/Compat", WINTER_VERSION).toDouble();
}

bool AbstractPlugin::isSupported() const
{
    return WINTER_VERSION >= compatVersion();
}

QStringList AbstractPlugin::plugins() const
{
    Q_D (const AbstractPlugin);
    const QVariant vrnt = d->settings->value ("Dependencies/Plugins");

    if (vrnt.isValid() && !vrnt.isNull()) {
        QStringList dep = vrnt.toString().split (";");
        dep.removeDuplicates();
        dep.removeAll ("None");
        dep.removeAll (QString::null);
        qDebug() << "Plug-ins: " << dep;
        return dep;
    }

    qDebug() << d->settings->fileName();
    QFile sett (d->settings->fileName());
    qDebug() << sett.readAll();
    return QStringList();
}

bool AbstractPlugin::hasNeededPlugins() const
{
    const QStringList deps = this->plugins();
    foreach (const QString dep, deps) {
        const QString depName = dep.split (" ").at (0);
        const QString depComparison = dep.split (" ").at (1);
        const QString depVersion = dep.split (" ").at (2);

        if (Factory::allPlugins().contains (depName)) {
            if (!Factory::loadedPlugins().contains (depName))
                qDebug() << "(core) [AbstractPlugin] Dependency" << depName
                         << "of" << this->name () << "isn't loaded.";

            const AbstractPlugin* plgn = Factory::obtainPlugin (depName);

            if (depComparison == "==") {
                if (! (depVersion.toDouble() == plgn->version())) {
                    qDebug() << "(core) [AbstractPlugin] " << this->name()
                             << "requires" << depName
                             << "to have a version of" << depVersion;
                    return false;
                }
            }
            else if (depComparison == ">") {
                if (! (depVersion.toDouble () > plgn->version())) {
                    qDebug() << "(core) [AbstractPlugin] " << this->name ()
                             << "requires" << depName
                             << "to have a version greater than" << depVersion;
                    return false;
                }
            }
            else if (depComparison == "<") {
                if (! (depVersion.toDouble () < plgn->version ())) {
                    qDebug() << "(core) [AbstractPlugin] " << this->name()
                             << "requires" << depName << "to have a version less than" << depVersion;
                    return false;
                }
            }
            else if (depComparison == ">=") {
                if (! (depVersion.toDouble () >= plgn->version ())) {
                    qDebug() << "(core) [AbstractPlugin] " << this->name()
                             << "requires" << depName
                             << "to have a version of at least" << depVersion;
                    return false;
                }
            }
            else if (depComparison == "==") {
                if (! (depVersion.toDouble () > plgn->version ())) {
                    qDebug() << "(core) [AbstractPlugin] " << this->name()
                             << "requires" << depName << "to have a version of at most" << depVersion;
                    return false;
                }
            }
            else {
                qDebug() << "(core) [AbstractPlugin] <" << this->name()
                         << "> : Invalid version string ("
                         << depComparison << ").";
            }
        }
    }

    return true;
}

QStringList AbstractPlugin::packages() const
{
    Q_D (const AbstractPlugin);
    QStringList dep = d->settings->value ("Dependencies/Packages").toStringList();
    dep.removeDuplicates();
    dep.removeAll ("None");
    return dep;
}

/// @note This method requires code from QPackageKit.
/// @note issue #0000029
bool AbstractPlugin::hasNeededPackages() const
{
    const QStringList deps = this->packages();

    foreach (const QString dep, deps) {
        const QString depName = dep.split (" ").at (0);
        const QString depComparison = dep.split (" ").at (1);
        const QString depVersion = dep.split (" ").at (2);
    }

    return true;
}

QVariant AbstractPlugin::attribute (const QString& p_attributePath) const
{
    Q_D (const AbstractPlugin);
    QVariant val = d->configuration->value (p_attributePath);

    if (val.isNull() || !val.isValid())
        val = d->configuration->value ("Configuration/" + QString (p_attributePath).replace ("/", ":"));

    return val;
}

void AbstractPlugin::setAttribute (const QString& p_attributePath, const QVariant& p_attributeValue)
{
    Q_D (AbstractPlugin);
    d->configuration->setValue (p_attributePath, p_attributeValue);
}

/// @note issue #0000030
void AbstractPlugin::resetAttributes()
{
    Q_D (AbstractPlugin);
    d->configuration->clear();
}

bool AbstractPlugin::loadLibrary() const
{
    Q_D (const AbstractPlugin);
    WINTER_APPLICATION::addLibraryPath (WINTER_PLUGIN_PATH);
    const QString plgnLibrary = d->settings->value ("Version/Library").toString();
    const QString plgPth = QString (WINTER_PLUGIN_PATH) + "/lib" + plgnLibrary + ".so";
    d->pluginLoader = new QPluginLoader (plgPth, Factory::instance());
    d->pluginLoader->setLoadHints (QLibrary::ResolveAllSymbolsHint | QLibrary::ExportExternalSymbolsHint | QLibrary::LoadArchiveMemberHint);
    qDebug() << "(plugin) [AbstractPlugin::loadLibrary()] Loaded library for " << name() << "?" << d->pluginLoader->load();

    if (!d->pluginLoader->isLoaded())
        qDebug() << "(plugin) [AbstractPlugin::loadLibrary()] Error loading library"
                 << plgPth << endl
                 << d->pluginLoader->errorString();

    return d->pluginLoader->isLoaded();
}

bool AbstractPlugin::loadRequiredComponents() const
{
    Q_D (const AbstractPlugin);

    if (!isSupported ()) {
        qWarning() << "(plugin) [Factory] Plug-in" << name () << "is incompatible with this version of Wintermute.";
        return false;
    }
    else
        qDebug() << "(plugin) [Factory] Plug-in" << name () << "v." << version() << "is compatible with this version of Wintermute.";

    if (!d->loadPackages()) {
        qWarning() << "(plugin) [Factory] Can't load dependency packages for plug-in" << name() << ".";
        return false;
    }

    if (!d->loadPlugins()) {
        qWarning() << "(plugin) [Factory] Can't load dependency plug-ins for plug-in" << name() << ".";
        return false;
    }

    return true;
}

AbstractPlugin* AbstractPlugin::obtainInstance() const
{
    Q_D (const AbstractPlugin);

    if (d->pluginLoader->isLoaded()) {
        QObject* plgnInstance = d->pluginLoader->instance();

        if (plgnInstance->inherits (staticMetaObject.className())) {
            return dynamic_cast< AbstractPlugin* > (plgnInstance);
        }
        else {
            qDebug() << "(core) [AbstractPlugin::obtainInstance()] The instance doesn't inherit from the abstract plug-in class.";
            return 0;
        }
    }

    return 0;
}

AbstractPlugin::~AbstractPlugin()
{
    Q_D (AbstractPlugin);
    d->pluginLoader->unload();
    d->pluginLoader->deleteLater();
    d->settings->sync();
    d->configuration->sync();
    d->configuration->deleteLater();
    d->settings->deleteLater();
}

#include "plugin.moc"
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;

