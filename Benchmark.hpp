#include <iostream>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>

/*	A Competitor stores one function to be compared
	m_name     -> its name
	m_function -> the actual function
	m_score    -> its score for the last execution
*/
class Competitor
{
public:
	// Create a competitor supporting various function initialization ways
	template<class T>
	Competitor(const std::string& name, const T& function) :
		m_name(name),
		m_function(function),
		m_score(0.0)
	{}

	// Runs the function and measures its execution time 
	void run()
	{
		std::chrono::steady_clock::time_point begin(std::chrono::steady_clock::now());
		std::chrono::steady_clock::time_point end;

		m_function();
		
		end = std::chrono::steady_clock::now();
		m_score = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count());
	}

	// Returns the competitor's name
	const std::string& getName() const { return m_name; }

	// Returns the competitor's score
	double getScore() const { return m_score; }

private:
	std::string           m_name;
	std::function<void()> m_function;
	double                m_score;
};


/*	A Challenge represents a set of competitors supposed to be doing the same thing
	m_name        -> its name
	m_competitors -> the competitors to compare
*/
class Challenge
{
public:
	Challenge(const std::string& name, std::vector<Competitor>	competitors) :
		m_name(name),
		m_competitors(competitors)
	{}

	// Run the function of each competitor
	void run()
	{
		std::cout << "-----[ " << m_name << " ]-----" << std::endl;
		for (Competitor& competitor : m_competitors)
		{
			competitor.run();
		}
	}

	// Display the results
	void showResults()
	{
		size_t longest_name = std::max_element(m_competitors.begin(), m_competitors.end(), [](const Competitor& c1, const Competitor& c2) {return c1.getName().size() < c2.getName().size(); })->getName().size();

		std::sort(m_competitors.begin(), m_competitors.end(), [](const Competitor& c1, const Competitor& c2) {return c1.getScore() < c2.getScore(); });
		double min = m_competitors.front().getScore();
		size_t max_score_size = static_cast<size_t>(log10(m_competitors.back().getScore()));

		for (const Competitor& competitor : m_competitors)
		{
			std::string name_alignment = "  ";
			for (size_t i(longest_name - competitor.getName().size()); i--;) name_alignment += " ";

			std::cout << "  " << competitor.getName() << name_alignment << competitor.getScore() * 0.000001 << " ms (" << int(competitor.getScore() / min * 100) << " % -> x" << int(competitor.getScore() / min) << ")" << std::endl;
		}
	}

private:
	std::string m_name;
	std::vector<Competitor>	m_competitors;
};


/*	A Benchmark represents a set of competitors supposed to be doing the same thing
	m_iteration_count -> how many times the Challenges will be executed
	m_challenges      -> the challenges to run
*/
class Benchmark
{
public:
	Benchmark(uint32_t iteration_count, const std::vector<Challenge>& challenges) :
		m_iteration_count(iteration_count),
		m_challenges(challenges)
	{}

	void run()
	{
		for (uint32_t i(m_iteration_count); i--;)
		{
			for (Challenge& challenge : m_challenges)
			{
				challenge.run();
				challenge.showResults();
				std::cout << std::endl;
			}
		}
	}

private:
	uint32_t m_iteration_count = 1;
	std::vector<Challenge> m_challenges;
};
