#include <iostream>
#include <chrono>
#include <ratio>
#include <cassert>

int main() {
	using namespace std::chrono;

	std::chrono::minutes leasure(5);
	std::chrono::minutes acmHour(40);
	std::chrono::minutes pair(0);
	std::chrono::weeks sem_dur(15);

	//����� ������������ ����
	pair += 2 * acmHour + leasure;
	assert(pair.count() == 85);

	year_month_day sem_start = 2025y / February / 1d;

	auto sem_end = sys_days(sem_start) + floor<std::chrono::days>(sem_dur);	

	std::cout << "Date of sem start: " << sem_start << '\n';
	std::cout << "Date of sem end: " << sem_end << '\n';

	int pairs_amount = 195;
	auto study_dur = pairs_amount * pair;
	auto hyp_sem_end = sys_days(sem_start) + floor<std::chrono::days>(study_dur);

	auto delta = sys_days(sem_end) - floor<std::chrono::days>(hyp_sem_end);
	
	//������� � h
	auto study_hours = std::chrono::duration_cast<std::chrono::hours>(study_dur);
	auto sem_hours = std::chrono::duration_cast<std::chrono::hours>(sem_dur);
	
	//������� � double. ���������� ����� �������� ����� � <double, h>, �������� ��?
	//��� ������� �������������� ����� � hours, ��������� ������� 0, ���� ��������� 100 � ��������� 10. ��� � �����, ��� ����� ����� �� �������
	auto share = std::chrono::duration<double>(study_hours) / std::chrono::duration<double>(sem_hours) * 100;
	
	std::cout << "Hypothetical date of sem end: " << hyp_sem_end << '\n';
	std::cout << "Delta(days): " << delta << '\n';
	//���� �� ��� �������  ���������� ������ �� ����������� �����������?
	printf("Share of pairs in sem = %4.2f \n", share);

}