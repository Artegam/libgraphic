#include <tests/LibGraphicTestManager.h>
#include <tests/ViewsTestManager.h>

int main(int argc, char** argv) {
  LibGraphicTestManager manager("GLOBAL");
  //Core lib
  manager.assert(new GraphicComponentTests());
  manager.assert(new GraphicCompositeTests());
  manager.assert(new ScreenTests());
  manager.assert(new TextTests());
  manager.assert(new InputTests());
  manager.assert(new SelectorTests());
  manager.assert(new DialogboxTests());
  manager.assert(new OpenDialogboxTests());
  manager.assert(new GotoDialogboxTests());
  manager.assert(new MenuTests());
  manager.assert(new HMenuTests());
  manager.assert(new VMenuTests());
  manager.assert(new ButtonTests());
  manager.assert(new ImageTests());
  manager.assert(new CellTests());
  manager.assert(new TableTests());
  manager.assert(new ScrollbarTests());
  manager.assert(new CalendarTests());
  manager.assert(new AgendaTests());
  manager.assert(new NodeTests());
  manager.assert(new ItemTests());
  manager.assert(new GroupItemTests());

  //Views
  manager.assert(new ViewTests());
  manager.assert(new NCursesTests());

  manager.execute();
  return manager.report();
}
