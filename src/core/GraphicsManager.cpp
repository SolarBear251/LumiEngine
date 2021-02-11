/**
 * @file       GraphicsManager.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Methods definitions of GraphicsManager
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include "core/GraphicsManager.h"

int Lumi::GraphicsManager::Initialize() { return 0; }

void Lumi::GraphicsManager::Finalize() {}

void Lumi::GraphicsManager::Tick() { Render(); }

void Lumi::GraphicsManager::Render() {}