#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

// Point class represents a 2D point
class Point {
public:
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};

// Cluster class represents a cluster of points
class Cluster {
public:
    Point centroid;
    std::vector<Point> points;

    // Calculate the centroid of the cluster
    void updateCentroid() {
        if (points.empty()) {
            return;
        }

        double sumX = 0.0, sumY = 0.0;
        for (const Point& point : points) {
            sumX += point.x;
            sumY += point.y;
        }

        centroid.x = sumX / points.size();
        centroid.y = sumY / points.size();
    }

    // Clear the points in the cluster
    void clearPoints() {
        points.clear();
    }
};

// Function to calculate the Euclidean distance between two points
double calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

// Function to assign points to the nearest cluster
void assignToClusters(const std::vector<Point>& data, const std::vector<Cluster>& clusters) {
    for (Point& point : const_cast<std::vector<Point>&>(data)) {
        double minDistance = std::numeric_limits<double>::max();
        int assignedCluster = 0;

        for (int i = 0; i < clusters.size(); ++i) {
            double distance = calculateDistance(point, clusters[i].centroid);
            if (distance < minDistance) {
                minDistance = distance;
                assignedCluster = i;
            }
        }

        clusters[assignedCluster].points.push_back(point);
    }
}

// Function to update cluster centroids
void updateClusterCentroids(std::vector<Cluster>& clusters) {
    for (Cluster& cluster : clusters) {
        cluster.updateCentroid();
    }
}

// Function to perform K-means clustering
void kMeans(std::vector<Point>& data, int k, int maxIterations) {
    // Initialize clusters with random centroids
    std::vector<Cluster> clusters;
    for (int i = 0; i < k; ++i) {
        int randomIndex = std::rand() % data.size();
        clusters.push_back({data[randomIndex], {}});
    }

    // Perform iterations
    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        // Assign points to clusters
        assignToClusters(data, clusters);

        // Update cluster centroids
        updateClusterCentroids(clusters);

        // Clear points in each cluster for the next iteration
        for (Cluster& cluster : clusters) {
            cluster.clearPoints();
        }
    }
}

int main() {
    // Set the seed for random number generation
    std::srand(std::time(0));

    // Generate random data
    std::vector<Point> data;
    for (int i = 0; i < 100; ++i) {
        data.push_back({static_cast<double>(std::rand() % 100), static_cast<double>(std::rand() % 100)});
    }

    // Perform K-means clustering with k=3 and 10 iterations
    int k = 3;
    int maxIterations = 10;
    kMeans(data, k, maxIterations);

    // Display the final clusters
    for (int i = 0; i < k; ++i) {
        std::cout << "Cluster " << i + 1 << " centroid: (" << clusters[i].centroid.x << ", " << clusters[i].centroid.y << ")\n";
        std::cout << "Points in Cluster " << i + 1 << ":\n";
        for (const Point& point : clusters[i].points) {
            std::cout << "(" << point.x << ", " << point.y << ")\n";
        }
        std::cout << "\n";
    }

    return 0;
}
