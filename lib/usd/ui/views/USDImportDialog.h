//
// Copyright 2019 Autodesk
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#pragma once

#include <mayaUsd/ui/api.h>

#include <memory>

#include <QtWidgets/QDialog>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QTimer>

#include <pxr/usd/usd/stage.h>

#include "IUSDImportView.h"
// #include "SpinnerOverlayWidget.h"
#include "TreeModel.h"
#include "USDSearchThread.h"

namespace Ui {
	class ImportDialog;
}

PXR_NAMESPACE_USING_DIRECTIVE

MAYAUSD_NS_DEF {

/**
 * \brief USD file import dialog.
 */
class MAYAUSD_UI_PUBLIC USDImportDialog
		: public QDialog
		, public IUSDImportView
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor.
	 * \param filename Absolute file path of a USD file to import.
	 * \param parent A reference to the parent widget of the dialog.
	 */
	explicit USDImportDialog(const std::string& filename, QWidget* parent = nullptr);

	//! Destructor.
	~USDImportDialog();

	// IUSDImportView overrides
	const std::string& filename() const override;
	const std::string& rootPrimPath() const override;
	UsdStagePopulationMask stagePopulationMask() const override;
	UsdStage::InitialLoadSet stageInitialLoadSet() const override;
	ImportData::PrimVariantSelections primVariantSelections() const override;
	bool execute() override;

protected:
	/**
	 * \brief callback function executed upon changing the text in the search box.
	 * \param searchFilter The new content of the search box.
	 */
	void onSearchFilterChanged(const QString& searchFilter);

	/**
	 * \brief Callback function executed upon selecting items in the TreeView.
	 * \param selectedItems The list of TreeView items which were selected.
	 * \param deselectedItems The list of TreeView items which were deselected.
	 */
	void onTreeViewSelectionChanged(const QItemSelection& selectedItems, const QItemSelection& deselectedItems);

protected:
	// Reference to the Qt UI View of the dialog:
	std::unique_ptr<Ui::ImportDialog> fUI;

	// Reference to the Model holding the structure of the USD file hierarchy:
	std::unique_ptr<TreeModel> fTreeModel;
	// Reference to the Proxy Model used to sort and filter the USD file hierarchy:
	std::unique_ptr<QSortFilterProxyModel> fProxyModel;

	// Reference to the thread used to perform Prim searches in the background:
	std::unique_ptr<USDSearchThread> fSearchThread;

	// Reference to the timer used to display a Spinner overlay on top of the TreeView in case of lengthy search
	// operations:
	std::unique_ptr<QTimer> fSearchTimer;

	// Reference to the USD Stage holding the list of Prims which could be imported:
	UsdStageRefPtr fStage;

	// The filename for the USD stage we opened.
	std::string fFilename;

	// The root prim path.
	mutable std::string fRootPrimPath;

// 	// TreeView overlay on which to display an animated Spinner or message to the User:
// 	std::unique_ptr<SpinnerOverlayWidget> fOverlay;
};

} // namespace MayaUsd
