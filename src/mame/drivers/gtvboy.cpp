// license:<license>
// copyright-holders:<author_name>
/***************************************************************************

    Skeleton for Gekken TV Boy

    Based on the analysis work by mr.tanam

***************************************************************************/

#include "emu.h"
#include "machine/ram.h"
#include "cpu/m6800/m6801.h"
#include "video/mc6847.h"
#include "emupal.h"
#include "screen.h"

#define MAIN_CLOCK XTAL(4'000'000)

class gtvboy_state : public driver_device
{
public:
	gtvboy_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_mc6847(*this, "mc6847")
		, m_ram(*this, RAM_TAG)
		// , m_palette(*this, "palette")
	{
	}

	void gtvboy(machine_config &config);

protected:
	virtual void machine_start() override;
	virtual void machine_reset() override;

	virtual void video_start() override;

    uint8_t mc6847_videoram_r(offs_t offset);

    uint8_t io_mc6847_r();
    void io_mc6847_w(uint8_t data);

private:
    void gtvboy_palette(palette_device &palette) const;

	void gtvboy_mem(address_map &map);

	required_device<cpu_device> m_maincpu;
    required_device<mc6847_base_device> m_mc6847;
    required_device<ram_device> m_ram;
};

void gtvboy_state::video_start()
{
}

void gtvboy_state::gtvboy_mem(address_map &map)
{
    map(0x0000, 0x0fff).ram(); // RAM
    // 0x80 to 0x100 is mapped to 0x00 to 0x7f ?

    map(0x1000, 0x1fff).ram(); // VRAM
    map(0x2000, 0x2000).rw(FUNC(gtvboy_state::io_mc6847_r), FUNC(gtvboy_state::io_mc6847_w));
	map(0xe800, 0xffff).rom(); // ROM
}


static INPUT_PORTS_START( gtvboy )
	/* dummy active high structure */
	PORT_START("SYSA")
	PORT_DIPNAME( 0x01, 0x00, "SYSA" )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x01, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x00, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x02, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x00, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x04, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x00, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x08, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x00, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x10, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x00, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x20, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x40, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x00, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x80, DEF_STR( On ) )

	/* dummy active low structure */
	PORT_START("DSWA")
	PORT_DIPNAME( 0x01, 0x01, "DSWA" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
INPUT_PORTS_END


void gtvboy_state::machine_start()
{
    m_mc6847->gm0_w(BIT(0x01, 0));
    m_mc6847->gm1_w(BIT(0x00, 1));
    //m_mc6847->gm2_w(BIT(data, 2));
    m_mc6847->intext_w(BIT(0x00, 2));
    m_mc6847->as_w(BIT(0x00, 3));
    m_mc6847->ag_w(BIT(0x10, 4));
    m_mc6847->css_w(BIT(0x20, 5));
}

void gtvboy_state::machine_reset()
{
}

void gtvboy_state::gtvboy_palette(palette_device &palette) const
{
}

void gtvboy_state::gtvboy(machine_config &config)
{
	M6801(config, m_maincpu, MAIN_CLOCK);
	m_maincpu->set_addrmap(AS_PROGRAM, &gtvboy_state::gtvboy_mem);

    SCREEN(config, "screen", SCREEN_TYPE_RASTER);
    mc6847_ntsc_device &vdg(MC6847_NTSC(config, "mc6847", XTAL(3'579'545)));
    vdg.set_screen("screen");
    vdg.input_callback().set(FUNC(gtvboy_state::mc6847_videoram_r));

    RAM(config, RAM_TAG).set_default_size("2K");
}

uint8_t gtvboy_state::mc6847_videoram_r(offs_t offset)
{
    m_mc6847->inv_w(BIT(m_ram->read(offset), 6));
    m_mc6847->as_w(BIT(m_ram->read(offset), 7));

    return m_ram->read(offset);
}

uint8_t gtvboy_state::io_mc6847_r()
{
    return 0;
}

void gtvboy_state::io_mc6847_w(uint8_t data)
{
    m_mc6847->as_w(BIT(data, 3));
    m_mc6847->ag_w(BIT(data, 4));
    m_mc6847->css_w(BIT(data, 5));
    m_mc6847->gm0_w(BIT(data, 1));
    m_mc6847->gm1_w(BIT(data, 0));
    m_mc6847->intext_w(BIT(data, 2));
}


/***************************************************************************

  Machine driver(s)

***************************************************************************/

namespace
{
ROM_START(gtvboy)
    ROM_REGION( 0x10000, "maincpu", ROMREGION_ERASEFF )
    ROM_LOAD( "rom6801.rom", 0xf000, 0x1000, BAD_DUMP CRC(aa27bc53) SHA1(2cb404d2279f114710cb756f5f085cb2b9ce7a1f) )
ROM_END

}

GAME( 1983, gtvboy,  0,  gtvboy,  gtvboy, gtvboy_state, empty_init, ROT0, "Gakken", "Gakken TV Boy", MACHINE_IS_SKELETON )
