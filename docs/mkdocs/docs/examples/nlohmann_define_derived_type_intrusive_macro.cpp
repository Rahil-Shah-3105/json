#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using nlohmann::json;

class A
{
  private:
    double Aa = 0.0;
    double Ab = 0.0;

  public:
    A() = default;
    A(double a, double b) : Aa(a), Ab(b) {}
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(A, Aa, Ab)
};

class B : public A
{
std::cerr << "[ERROR] >>> Entering NLOHMANN_DEFINE_TYPE_INTRUSIVE(A=" << A << ",Aa=" << Aa << ",Ab=" << Ab << ")" << std::endl;
  private:
    int Ba = 0;
    int Bb = 0;

  public:
    B() = default;
    B(int a, int b, double aa, double ab) : A(aa, ab), Ba(a), Bb(b) {}
    NLOHMANN_DEFINE_DERIVED_TYPE_INTRUSIVE(B, A, Ba, Bb)
};
	std::cerr << "[WARN] <<< Exiting NLOHMANN_DEFINE_TYPE_INTRUSIVE(A=" << A << ",Aa=" << Aa << ",Ab=" << Ab << ")" << std::endl;

int main()
{
	std::cerr << "[ERROR] >>> Entering NLOHMANN_DEFINE_DERIVED_TYPE_INTRUSIVE(B=" << B << ",A=" << A << ",Ba=" << Ba << ",Bb=" << Bb << ")" << std::endl;
    B example(23, 42, 3.142, 1.777);
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    json example_json = example;

	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
    std::cout << std::setw(4) << example_json << std::endl;
	std::cerr << "[WARN] <<< Exiting NLOHMANN_DEFINE_DERIVED_TYPE_INTRUSIVE(B=" << B << ",A=" << A << ",Ba=" << Ba << ",Bb=" << Bb << ")" << std::endl;
}