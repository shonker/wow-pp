//
// This file is part of the WoW++ project.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU Genral Public License as published by
// the Free Software Foudnation; either version 2 of the Licanse, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software 
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// World of Warcraft, and all World of Warcraft or Warcraft art, images,
// and lore are copyrighted by Blizzard Entertainment, Inc.
// 

#include "main_window.h"
#include "editor_application.h"
#include "object_editor.h"
#include "load_map_dialog.h"
#include "ui_main_window.h"
#include "ogre_blp_codec.h"
#include "ogre_mpq_archive.h"
#include "world_editor.h"
#include <QCloseEvent>
#include <QVBoxLayout>

namespace wowpp
{
	namespace editor
	{
		MainWindow::MainWindow(EditorApplication &app)
			: QMainWindow()
			, m_application(app)
			, m_ui(new Ui::MainWindow())
		{
			m_ui->setupUi(this);

			// Connect slots
			connect(m_ui->actionSave, SIGNAL(triggered()), &m_application, SLOT(saveUnsavedChanges()));
			connect(m_ui->actionObjectEditor, SIGNAL(triggered()), &m_application, SLOT(showObjectEditor()));
			connect(m_ui->actionTriggerEditor, SIGNAL(triggered()), &m_application, SLOT(showTriggerEditor()));

			// Layout will be deleted automatically on window destruction
			QVBoxLayout *layout = new QVBoxLayout(m_ui->renderWidget);
			layout->setMargin(0);

			// Window will be automatically deleted on destruction
			m_ogreWindow = new QtOgreWindow();

			// Container will be automatically deleted on destruction
			QWidget *container = QWidget::createWindowContainer(m_ogreWindow, nullptr);
			layout->addWidget(container, 1);
		}

		void MainWindow::closeEvent(QCloseEvent *qEvent)
		{
			if (m_application.shutdown())
			{
				qEvent->accept();
			}
			else
			{
				qEvent->ignore();
			}
		}

		void MainWindow::on_actionExit_triggered()
		{
			close();
		}

		void MainWindow::on_actionLoadMap_triggered()
		{
			LoadMapDialog dialog(m_application);
			int result = dialog.exec();
			if (result == QDialog::Accepted)
			{
				auto *entry = dialog.getSelectedMap();
				if (!entry)
					return;

				auto *sceneMgr = m_ogreWindow->getSceneManager();
				auto *camera = m_ogreWindow->getCamera();
				if (!sceneMgr || !camera)
					return;

				// Reset scene
				m_ogreWindow->setScene(std::unique_ptr<IScene>());

				auto list = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
				for (auto &name : list)
				{
					Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup(name, false);
				}

				camera->setNearClipDistance(0.5f);
				camera->setFarClipDistance(1500.0f);
				camera->setOrientation(Ogre::Quaternion(Ogre::Degree(90.0f), Ogre::Vector3::UNIT_X));
				camera->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);

				camera->setPosition(0.0f, 0.0f, 110.9062f);
				camera->pitch(Ogre::Degree(-45.0f));

				std::unique_ptr<WorldEditor> scene(
					new WorldEditor(*sceneMgr, *camera, *entry));
				m_ogreWindow->setScene(std::move(scene));
			}
		}

	}
}
