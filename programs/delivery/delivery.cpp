#include <iostream>
#include <iomanip>

const int B = 12;

double calc_miles(double m_1, double m_2)
{
	return m_2 - m_1;
}

double calc_gas(double m_total)
{
	return m_total / 22 * 1.55;
}

double calc_income(double deliveries, double tips)
{
	return deliveries + tips;
}

double calc_profit(double income, double gas)
{
	return income - gas;
}

double calc_per_hour(double profit, double hours)
{
	return profit / hours;
}

void user_input(double& m_start, double& m_end, double& hours, double& deliveries, double& tips, double& gas)
{
	using namespace std;
	cout << "Starting miles: ";
	cin >> m_start;
	cout << "Ending miles: ";
	cin >> m_end;
	cout << "Hours: ";
	cin >> hours;
	cout << "$ from deliveries: ";
	cin >> deliveries;
	cout << "$ from tips: ";
	cin >> tips;
}

void print_results(double m_total, double income, double profit, double avg_per_hour)
{
	using namespace std;
	cout << '\n' <<left <<  setw(B) << "Miles" << setw(B) << "Income" << setw(B) << "Profit" << setw(B) << "Avg $/hr";
	cout << endl;
	cout << "---------------------------------------------------------\n";
	cout << left << setw(B) <<  m_total 
	     << fixed << setprecision(2) << '$' << setw(B) << income 
	     << '$' << setw(B) << profit << '$' << setw(B) << avg_per_hour << endl;

}

int main()
{
	double m_start, m_end, m_total;
	double hours, avg_per_hour;
	double deliveries, tips, gas, income, profit;

	user_input(m_start, m_end, hours, deliveries, tips, gas);
	m_total = calc_miles(m_start, m_end);
	gas = calc_gas(m_total);
	income = calc_income(deliveries, tips);
	profit = calc_profit(income, gas);
	avg_per_hour = calc_per_hour(profit, hours);

	print_results(m_total, income, profit, avg_per_hour);

	
	return 0;
}
