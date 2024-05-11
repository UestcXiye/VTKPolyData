#include "VTKPolyData.h"

#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkShrinkPolyData.h>

/* 实例 1：8 个点表示一个 vtkPolyData
VTKPolyData::VTKPolyData(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_pVTKWidget = new QVTKOpenGLNativeWidget();
	this->setCentralWidget(_pVTKWidget);
	// this->showMaximized();

	// 1. generate data
	vtkNew<vtkPoints> points; // 节点
	points->InsertPoint(0, 0, 0, 0);
	points->InsertPoint(1, 0, 1, 0);
	points->InsertPoint(2, 1, 0, 0);
	points->InsertPoint(3, 1, 1, 0);
	points->InsertPoint(4, 2, 0, 0);
	points->InsertPoint(5, 2, 1, 0);
	points->InsertPoint(6, 3, 0, 0);
	points->InsertPoint(7, 3, 1, 0);

	vtkNew<vtkCellArray> strips; // 单元
	strips->InsertNextCell(8);
	strips->InsertCellPoint(0);
	strips->InsertCellPoint(1);
	strips->InsertCellPoint(2);
	strips->InsertCellPoint(3);
	strips->InsertCellPoint(4);
	strips->InsertCellPoint(5);
	strips->InsertCellPoint(6);
	strips->InsertCellPoint(7);

	vtkNew<vtkPolyData> poly;
	poly->SetPoints(points);
	// poly->SetVerts(strips);
	poly->SetLines(strips);
	// poly->SetStrips(strips);

	// 2. filter

	// 3. mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	// 4. actor
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

	// 5. renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(0.3, 0.6, 0.3);

	// 6. connect
	mapper->SetInputData(poly);
	actor->SetMapper(mapper);
	renderer->AddActor(actor);

	this->_pVTKWidget->renderWindow()->AddRenderer(renderer);
	this->_pVTKWidget->renderWindow()->Render();
}
*/

// 实例 2：立方体

VTKPolyData::VTKPolyData(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_pVTKWidget = new QVTKOpenGLNativeWidget();
	this->setCentralWidget(_pVTKWidget);
	// this->showMaximized();

	// 1. generate data
	std::array<std::array<double, 3>, 8> pts = {
		{
			{{0,0,0}},
			{{1,0,0}},
			{{1,1,0}},
			{{0,1,0}},
			{{0,0,1}},
			{{1,0,1}},
			{{1,1,1}},
			{{0,1,1}}
		}
	};
	std::array<std::array<vtkIdType, 4>, 6> ordering = {
		{
			{{0,1,2,3}},
			{{4,5,6,7}},
			{{0,1,5,4}},
			{{1,2,6,5}},
			{{2,3,7,6}},
			{{3,0,4,7}}
		}
	};

	vtkNew<vtkPoints> points;
	vtkNew<vtkCellArray> polys;
	vtkNew<vtkFloatArray> scalars;
	vtkNew<vtkPolyData> cube;

	for (size_t i = 0; i < pts.size(); i++)
	{
		points->InsertPoint(i, pts[i].data());
		scalars->InsertTuple1(i, i);
	}

	for (auto&& i : ordering)
		polys->InsertNextCell(vtkIdType(i.size()), i.data());

	cube->SetPoints(points);
	cube->SetPolys(polys);
	cube->GetPointData()->SetScalars(scalars);

	// 2. filter

	// 3. mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	// 4. actor
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

	// 5. renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(0.3, 0.6, 0.3);

	// 6. connect
	mapper->SetInputData(cube);
	mapper->SetScalarRange(cube->GetScalarRange());
	actor->SetMapper(mapper);
	renderer->AddActor(actor);

	this->_pVTKWidget->renderWindow()->AddRenderer(renderer);
	this->_pVTKWidget->renderWindow()->Render();
}

VTKPolyData::~VTKPolyData()
{}
