#include "Subject.h"

int main(void) {
    Subject subj;

	Wrapper wrapper1(&subj, &Subject::f1, { {"arg1", 0}, {"arg2", 0} });
	Wrapper wrapper2(&subj, &Subject::f2, { {"arg1", 0} });
	Wrapper wrapper3(&subj, &Subject::f3, { {"arg1", 0}, {"arg2", 0} });

	Engine engine;

    engine.register_command(&wrapper1, "command1");
	engine.register_command(&wrapper2, "command2");
	engine.register_command(&wrapper3, "command3");

	std::cout << engine.execute("command1", { {"arg1",4},{"arg2",5} }) << std::endl;
	std::cout << engine.execute("command2", { {"arg1",16} }) << std::endl;
	std::cout << engine.execute("command3", { {"arg1",11},{"arg2",12} }) << std::endl;

	// excepions
	engine.register_command(&wrapper1, "command1");
	engine.execute("command4", { {"arg1",11},{"arg2",12} });
	engine.execute("command1", { {"arg1",4},{"arg2",5},{"arg3",6} });

}