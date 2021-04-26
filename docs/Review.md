## Meets Specifications

Dear Excellent Student,

You put a lot of effort into this project and I think it was worth it because
you implemented a very useful piece of code. Congratulations! Keep up the good
work for the next project!

## Extra Material

You could refer to these resources for more insight on the subject matter.

* [Automating tuning of PID Controllers](https://www.researchgate.net/post/Automating_tuning_of_PID_Controllers)
* [On Automation of the PID Tuning Procedure](https://www.semanticscholar.org/paper/On-Automation-of-the-PID-Tuning-Procedure-Soltesz/04e222cb17def7b940b8487c98a55f96a9dea1aa)
* [Tuning a PID Controller](https://www.omega.com/en-us/resources/tuning-a-pid-controller)
* [Automatic Controller Tuning using Relay-based Model Identification.](https://portal.research.lu.se/ws/files/33100749/ThesisJosefinBerner.pdf)

Also, take a look at these topics for more reading.

* [PID controller](https://en.wikipedia.org/wiki/PID_controller)
* [PID Explained for Process Engineers: Part 2 - Tuning Coefficients.](https://www.aiche.org/resources/publications/cep/2016/february/pid-explained-process-engineers-part-2-tuning-coefficients)

### Compilation

**Code must compile without errors with `cmake` and `make`. Given that we've
made CMakeLists.txt as general as possible, it's recommend that you do not
change it unless you can guarantee that your changes will still compile on any
platform.**

Awesome, your project compiles with `cmake && make`. For more information on
this build tool, refer to the following:

* https://cmake.org/runningcmake/
* https://rix0r.nl/blog/2015/08/13/cmake-guide/
* https://cmake.org/cmake/help/latest/guide/tutorial/index.html
* http://preshing.com/20170511/how-to-build-a-cmake-based-project/

### Implementation

**It's encouraged to be creative, particularly around hyper-parameter
tuning/optimization. However, the base algorithm should follow what's presented
in the lessons.**

Very good implementation, your code follows the general guidelines of the PID
algorithm. In addition to that, I liked the fact that you used another instance
of the PID controller to handle the throttle.

### Reflection

**Student describes the effect of the P, I, D component of the PID algorithm in
their implementation. Is it what you expected?

Visual aids are encouraged, i.e. record of a small video of the car in the
simulator and describe what each component is set to.**

You clearly passed this requirement. you explained the effect of each of the P,
I , D components on the behavior of the car. One way to improve your write up
will be to actually discuss and contrast the actual behavior of the car with the
expected behavior of the car under various conditions including a P controller,
a D controller and other types of controllers.

You should also refer to the following links that have some more information on
the role of each component.

* https://www.youtube.com/watch?v=4Y7zG48uHRo&t=31s
* https://www.wikiwand.com/en/PID_controller#/Derivative_term
* http://oa.upm.es/30015/1/INVE_MEM_2013_165545.pdf

**Student discusses how they chose the final hyperparameters (P, I, D
coefficients). This could be have been done through manual tuning, twiddle, SGD,
or something else, or a combination!**

Awesome! You have found out the most optimized parameters by manual tuning.

### Suggestion

In order to fine tune parameters using twiddle algorithm, you should run it
first for n-steps and then save the optimized values. Tune parameters at each
frame is not reasonable because the system is changing all the time, and average
the total CTE for a certain time would be better.

Here are some online resources for better understanding the twiddle algorithm:

* https://github.com/justinlee007/CarND-PID-Control-Project
* http://georgegillard.com/programmingguides/introduction_to_pid_controllers_ed2-pdf?format=raw
* https://medium.com/intro-to-artificial-intelligence/pid-controller-udacitys-self-driving-car-nanodegree-c4fd15bdc981
* https://github.com/RomanoViolet/Udacity-PID-Controller
* https://www.youtube.com/watch?v=2uQ2BSzDvXs
* https://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops

### Simulation

**No tire may leave the drivable portion of the track surface. The car may not
pop up onto ledges or roll over any surfaces that would otherwise be considered
unsafe (if humans were in the vehicle).**

Nice work! The car drives around the track successfully without any tires
leaving the drivable portion of the track surface.