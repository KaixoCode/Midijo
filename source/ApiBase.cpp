#include "Midijo/ApiBase.hpp"

namespace Midijo
{

    void ApiBase::HandleEvents()
    {
        std::lock_guard _{ m_Lock };
        while (!m_EventQueue.empty())
        {
            listener.HandleEvent(*m_EventQueue.front());
            m_EventQueue.pop();
        }
    }

    bool ApiBase::HandleEvent()
    {
        std::lock_guard _{ m_Lock };
        if (!m_EventQueue.empty())
        {
            listener.HandleEvent(*m_EventQueue.front());
            m_EventQueue.pop();
            return true;
        }
        return false;
    }

}