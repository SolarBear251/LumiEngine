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

#include <lumi/core/GraphicsManager.h>

int lumi::GraphicsManager::Initialize() { return 0; }

void lumi::GraphicsManager::Finalize() {}

void lumi::GraphicsManager::Tick() { Render(); }

void lumi::GraphicsManager::Render() {}