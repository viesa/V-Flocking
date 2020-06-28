#pragma once

#include <set>

#include "VoidBody.h"
#include "Camera.h"

class Boid
{
public:
    Boid(const sf::Vector2f &position);

    bool operator==(const Boid &otherBoid) { return m_position == otherBoid.m_position; }

    void Update();

    void DrawBody() const;
    void DrawSight() const;
    void DrawNeighbors() const;
    void DrawVisibleNeighbors() const;
    void DrawVelocity() const;
    void DrawAcceleration() const;

    sf::Vector2f GetSeparationForce() const;
    sf::Vector2f GetAlignmentForce() const;
    sf::Vector2f GetCohesionForce() const;

    void AddNeighbor(const Boid *boid) { m_neighbors.emplace(boid); }
    void AddVisibleNeighbor(const Boid *boid) { m_visibleNeighbors.emplace(boid); }
    void ClearNeighbors() noexcept { m_neighbors.clear(); }
    void ClearVisibleNeighbors() noexcept { m_visibleNeighbors.clear(); }
    std::set<const Boid *> GetNeighbors() const noexcept { return m_neighbors; }
    std::set<const Boid *> GetVisibleNeighbors() const noexcept { return m_visibleNeighbors; }

    void ApplyForce(const sf::Vector2f &force) noexcept;

    const sf::Vector2f &GetPosition() const noexcept { return m_position; }
    float GetSightRadius() const noexcept { return m_sightRadius; }
    float GetSightAngle() const noexcept { return m_sightAngle; }
    sf::Vector2f GetForward() const noexcept;
    std::pair<sf::Vector2f, sf::Vector2f> GetSightBounds() const;
    sf::Vector2f GetVelocity() const noexcept { return m_velocity; };
    float GetSeparationMultiplier() const noexcept { return m_separationMultiplier; }
    float GetAlignmentMultiplier() const noexcept { return m_alignmentMultiplier; }
    float GetCohesionMultiplier() const noexcept { return m_cohesionMultiplier; }

    void SetPosition(const sf::Vector2f &position) noexcept { m_position = position; }
    void SetSeparationMultiplier(float multiplier) noexcept { m_separationMultiplier = multiplier; }
    void SetAlignmentMultiplier(float multiplier) noexcept { m_alignmentMultiplier = multiplier; }
    void SetCohesionMultiplier(float multiplier) noexcept { m_cohesionMultiplier = multiplier; }

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;

    float m_minSpeed;
    float m_maxSpeed;

    float m_separationMultiplier;
    float m_alignmentMultiplier;
    float m_cohesionMultiplier;

    std::set<const Boid *> m_neighbors;
    std::set<const Boid *> m_visibleNeighbors;

    sf::Color m_bodyColor;

    float m_sightRadius;
    float m_sightAngle;

    // Saved because it can't be calculated if velocity is zero
    mutable sf::Vector2f m_forward;
};