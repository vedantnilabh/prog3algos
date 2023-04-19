#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a function to determine if applicant a is better than applicant b in both WPM and IPM
bool is_better(const pair<float, float>& a, const pair<float, float>& b) {
    return (a.first > b.first) && (a.second < b.second);
}

// Define the recursive function to find the best applicants
vector<pair<float, float>> find_best_applicants(const vector<pair<float, float>>& applicants) {
    // Base case: if there's only one applicant, return it
    if (applicants.size() == 1) {
        return applicants;
    }

    // Divide the applicants into two groups
    int mid = applicants.size() / 2;
    vector<pair<float, float>> left_group(applicants.begin(), applicants.begin() + mid);
    vector<pair<float, float>> right_group(applicants.begin() + mid, applicants.end());

    // Recursively find the best applicants of each group
    vector<pair<float, float>> left_best = find_best_applicants(left_group);
    vector<pair<float, float>> right_best = find_best_applicants(right_group);

    // Combine the results of the two sets to form the final solution
    vector<pair<float, float>> best_applicants;
    merge(left_best.begin(), left_best.end(), right_best.begin(), right_best.end(), back_inserter(best_applicants), [&](const pair<float, float>& a, const pair<float, float>& b) {
        return is_better(a, b);
    });

    // Remove applicants that are not eligible
    vector<pair<float, float>> eligible_applicants;
    for (const auto& a : best_applicants) {
        bool is_eligible = all_of(applicants.begin(), applicants.end(), [&](const pair<float, float>& b) {
            return (&a != &b) && !is_better(b, a);
        });
        if (is_eligible) {
            eligible_applicants.push_back(a);
        }
    }

    return eligible_applicants;
}

// Define the public function that calls the recursive function and returns a vector of indices of the best applicants
vector<int> BestApplicants(const vector<pair<float, float>>& applicants) {
    // Find the best applicants
    vector<pair<float, float>> best_applicant_scores = find_best_applicants(applicants);

    // Create a vector of indices of the best applicants
    vector<int> best_applicants;
    for (int i = 0; i < applicants.size(); i++) {
        if (find(best_applicant_scores.begin(), best_applicant_scores.end(), applicants[i]) != best_applicant_scores.end()) {
            best_applicants.push_back(i);
        }
    }

    return best_applicants;
}










