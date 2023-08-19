#include <winui.h>

#include <map>

#include <fstream>

#define JSON_TRY_USER if (true)
#define JSON_CATCH_USER(exception) if (false)
#define JSON_THROW_USER(exception)

#include <nlohmann/json.hpp>

std::map<std::string, unsigned char> KEYOPTIONS {
    { "Backspace", VK_BACK },
    { "Tab", VK_TAB },
    { "Shift", VK_SHIFT },
    { "Control", VK_CONTROL },
    { "Alt", VK_MENU },
    { "Caps Lock", VK_CAPITAL },
    { "Escape", VK_ESCAPE },
    { "Space", VK_SPACE },
    { "Page Up", VK_PRIOR },
    { "Page Down", VK_NEXT },
    { "End", VK_END },
    { "Home", VK_HOME },
    { "Left Arrow", VK_LEFT },
    { "Right Arrow", VK_RIGHT },
    { "Up Arrow", VK_UP },
    { "Down Arrow", VK_DOWN },
    { "Select", VK_SELECT },
    { "Enter", VK_EXECUTE },
    { "Delete", VK_DELETE },
    { "0", 0x30 },
    { "1", 0x31 },
    { "2", 0x32 },
    { "3", 0x33 },
    { "4", 0x34 },
    { "5", 0x35 },
    { "6", 0x36 },
    { "7", 0x37 },
    { "8", 0x38 },
    { "9", 0x39 },
    { "A", 0x41 },
    { "B", 0x42 },
    { "C", 0x43 },
    { "D", 0x44 },
    { "E", 0x45 },
    { "F", 0x46 },
    { "G", 0x47 },
    { "H", 0x48 },
    { "I", 0x49 },
    { "J", 0x4A },
    { "K", 0x4B },
    { "L", 0x4C },
    { "M", 0x4D },
    { "N", 0x4E },
    { "O", 0x4F },
    { "P", 0x50 },
    { "Q", 0x51 },
    { "R", 0x52 },
    { "S", 0x53 },
    { "T", 0x54 },
    { "U", 0x55 },
    { "V", 0x56 },
    { "W", 0x57 },
    { "X", 0x58 },
    { "Y", 0x59 },
    { "Z", 0x5A },
    { "Win Left", VK_LWIN },
    { "Win Right", VK_RWIN },
};

struct Config
{
    std::vector<int> next;
    std::vector<int> prev;
    std::vector<int> play;
};

void
from_json(const nlohmann::json& j, Config& c)
{
    j.at("next").get_to(c.next);
    j.at("prev").get_to(c.prev);
    j.at("play").get_to(c.play);
}

void
to_json(nlohmann::json& j, const Config& c)
{
    j = {
        { "next", c.next },
        { "prev", c.prev },
        { "play", c.play }
    };
}

class KeySelect
{
public:
    KeySelect() : m_hwnd(NULL), m_offset(0) {

    }

    KeySelect(HWND hwnd, int offset) : m_hwnd(hwnd), m_offset(offset) {
        CreateUI();
    }

    void
    CreateUI()
    {
        for (int i = 0; i < 3; i++)
        {
            m_keys.push_back(winui::ComboBox({ 150, 400 }, { (150 * i) + 5, (30 * m_offset) + 10 }));
        }
    }

    void
    Draw()
    {
        std::vector<std::string> keys;
        for (const auto& [key, _] : KEYOPTIONS)
        {
            keys.push_back(key);
        }
        for (auto& key : m_keys) {
            key.Draw(m_hwnd);
            key.AddOptions(keys);
        }
    }

    std::vector<int>
    GetSelected() const
    {
        std::vector<int> selected;
        for (const auto& key : m_keys) {
            selected.push_back(KEYOPTIONS[key.GetSelectedValue()]);
        }
        return selected;
    }

    void 
    SetSelected(const std::vector<int>& selected)
    {
        for (int i = 0; i < 3; i++)
        {
            int value = selected[i];
            auto it = std::find_if(std::begin(KEYOPTIONS), std::end(KEYOPTIONS),
                [&value](const auto& p)
                {
                    return p.second == value;
                });
            m_keys[i].SetSelectedItem((*it).first);
        }
    }

private:
    int m_offset;
    std::vector<winui::ComboBox> m_keys;
    HWND m_hwnd;
};

KeySelect next;
KeySelect prev;
KeySelect play;

int
WINAPI
WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR pCmdLine, _In_ int nCmdShow)
{
    winui::Window window(hInstance, "MediaConfig", winui::util::Vector2i(470, 300));

    next = KeySelect(window.GetHandle(), 0);
    prev = KeySelect(window.GetHandle(), 1);
    play = KeySelect(window.GetHandle(), 2);

    std::ifstream ifs("config.mediakeys");
    if (ifs.is_open())
    {
        Config c = nlohmann::json::parse(ifs).get<Config>();
        next.SetSelected(c.next);
        prev.SetSelected(c.prev);
        play.SetSelected(c.play);
    }

    next.Draw();
    prev.Draw();
    play.Draw();

    winui::Button save("Save", { 100, 25 }, { window.GetSize().x - 120, window.GetSize().y - 65 });
    save.AddEventListener([]()
    { 
        Config c;
        c.next = next.GetSelected();
        c.prev = prev.GetSelected();
        c.play = play.GetSelected();
        nlohmann::json j = c;
        OutputDebugString(j.dump(4).c_str());
    });
    save.Draw(window.GetHandle());

    window.Show();
}